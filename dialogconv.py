#!/usr/bin/env python

import tkinter as tk
import tkinter.ttk as ttk
import re

# Shortcuts and escape characters for the input text and which character they correspond to in the output
sedtab = {
    r"\.":           r"…",
    r"$":            r"¥",
    r"\qo":          r"“",
    r"\qc":          r"”",
    r"\m":           r"♂",
    r"\f":           r"♀",
    r"\au":          r"{UP_ARROW}",
    r"\ad":          r"{DOWN_ARROW}",
    r"\al":          r"{LEFT_ARROW}",
    r"\ar":          r"{RIGHT_ARROW}",
    r"\e":           r"é",
    r"[player]":     r"{PLAYER}",
    r"[rival]":      r"{RIVAL}",
    r"[buffer1]":    r"{STR_VAR_1}",
    r"[buffer2]":    r"{STR_VAR_2}",
    r"[buffer3]":    r"{STR_VAR_3}",
    r"[buffer4]":    r"{STR_VAR_4}",
    r"[pause 30]":   r"{PAUSE 30}",
}

kerntab = {
    r" ":                4,
    r".":                5,
    r"!":                5,
    r"?":                5,
    r",":                5,
    r";":                5,
    r":":                5,
    r"¥":                8,
    r"“":                8,
    r"”":                8,
    r"'":                8,
    r"♂":                8,
    r"♀":                8,
    r"+":                8,
    r"{UP_ARROW}":       10,
    r"{DOWN_ARROW}":     10,
    r"{LEFT_ARROW}":     10,
    r"{RIGHT_ARROW}":    10,
    r"{PLAYER}":         42,
    r"{RIVAL}":          42,
    r"{STR_VAR_1}":      60,
    r"{STR_VAR_2}":      60,
    r"{STR_VAR_3}":      60,
    r"{STR_VAR_4}":      60,
}

kerntabdef = 6

mode_lengths = {
    "String": 198,
    "NPC": 198,
    "Sign": 198,
    "Script": 198,
    "YesNo": 198,
    "Dad": 198,
    "Dex": 235,
    "Move": 102,
    "Item": 193,
}

current_mode = "String"
kernmax = mode_lengths[current_mode]
ui = {}

def fixline(line):
    # Handle \p{number} before regular sedtab
    # Support both \p<number> and \p{number} syntaxes
    line = re.sub(r'\\p\{?(\d+)\}?', lambda m: f'{{PAUSE {m.group(1)}}}', line)

    for k in sedtab:
        line = line.replace(k, sedtab[k])
    return line

def countpx(line):
    fixed = fixline(line)
    tokens = re.findall(r'\{.*?\}|\S|\s', fixed)
    length = 0
    for token in tokens:
        if re.match(r'\{PAUSE \d+\}', token):
            continue  # Zero width
        length += kerntab.get(token, kerntabdef)
    return length

def fixtext(txt):
    global current_mode
    txt = txt.strip()
    if not txt:
        return ""

    lines = [fixline(line.strip()) for line in txt.splitlines()]
    formatted_lines = []
    use_newline = True

    for i, line in enumerate(lines):
        if current_mode in ["String", "NPC", "Script", "Dad", "YesNo","Sign"]:
            if use_newline:
                formatted_lines.append(f'{line}\\n')
                use_newline = False
            elif not line:
                formatted_lines[-1] = formatted_lines[-1][:-2] + "\\p"
                use_newline = True
            elif i == len(lines) - 1:
                formatted_lines.append(line)
            else:
                formatted_lines.append(f'{line}\\l')
        else:
            formatted_lines.append(line)

    if current_mode == "String":
        fixed = ''.join([f'\t.string "{line}"\n' for line in formatted_lines[:-1]])
        fixed += f'\t.string "{formatted_lines[-1]}$"'
    elif current_mode == "NPC":
        fixed = 'script Script_Name {\n\tmsgbox("' + ''.join(formatted_lines) + '", MSGBOX_NPC)\n}\n\n'
    elif current_mode == "Sign":
        fixed = 'script Script_Name {\n\tmsgbox("' + ''.join(formatted_lines) + '", MSGBOX_SIGN)\n\n}\n\n'
    elif current_mode == "Script":
        fixed = 'msgbox("' + ''.join(formatted_lines) + '", MSGBOX_DEFAULT)'
    elif current_mode == "Dad":
        fixed = 'script Script_Name {\n\tlock\n\tfaceplayer\n\ttextcolor(0)\n\tmsgbox("' + ''.join(formatted_lines) + '", MSGBOX_DEFAULT)\n\tcall(EventScript_DadHeal)\n\trelease\n\tend\n}\n'  
    elif current_mode == "YesNo":
        fixed = 'msgbox("' + ''.join(formatted_lines) + '", MSGBOX_YESNO)\nif(var(VAR_RESULT)) {\n\t\n}'  
    elif current_mode == "Dex":
        fixed = '\n'.join([f'\t"{line}\\n"' if i < len(lines) - 1 else f'\t"{line}"' for i, line in enumerate(lines)]) + ');'
    elif current_mode == "Move":
        fixed = '("' + '\\n'.join(lines) + '");'
    elif current_mode == "Item":
        fixed = '\\\\n'.join(lines) + '",'
    else:
        fixed = '\n'.join(lines)

    if current_mode in ["Script", "Dad", "YesNo"]:
        body = ''.join(fixed)

        # Insert human-readable newlines
        body = body.replace("msgbox(\"", "msgbox(\n\t\"")
        body = body.replace("\\n", "\\n\"\n\t\"")
        body = body.replace("\\l", "\\l\"\n\t\"")
        body = body.replace("\\p", "\\p\"\n\n\t\"")

        # Remove extra newline at very end if present
        if body.endswith("\n"):
            body = body[:-1]
        
        fixed = body


    if current_mode in ["NPC", "Sign",]:
        body = ''.join(fixed)

        # Insert human-readable newlines
        body = body.replace("msgbox(\"", "msgbox(\n\t\"")
        body = body.replace("\\n", "\\n\"\n\t\"")
        body = body.replace("\\l", "\\l\"\n\t\"")
        body = body.replace("\\p", "\\p\"\n\n\t\"")

        # Remove extra newline at very end if present
        if body.endswith("\n"):
            body = body[:-1]
        
        fixed = body

    return fixed

def click():
    content = ui["inbox"].get(1.0, tk.END)
    formatted_content = fixtext(content)
    ui["outbox"].config(state=tk.NORMAL)
    ui["outbox"].delete(1.0, tk.END)
    ui["outbox"].insert(1.0, formatted_content)
    ui["outbox"].config(state=tk.DISABLED)
    ui["win"].clipboard_clear()
    ui["win"].clipboard_append(formatted_content)

def update_line_length(event):
    line = ui["inbox"].get("insert linestart", "insert lineend")
    length = countpx(line)
    ui["length_label"].config(text=f"Line length: {length}px")
    if length > kernmax:
        ui["inbox"].tag_configure("exceed", foreground="red", font=("TkDefaultFont", 10, "bold"))
        ui["inbox"].tag_add("exceed", "insert linestart", "insert lineend")
    else:
        ui["inbox"].tag_remove("exceed", "insert linestart", "insert lineend")

def change_mode():
    global current_mode, kernmax
    current_mode = ui["mode_var"].get()
    kernmax = mode_lengths[current_mode]
    update_line_length(None)

def toggle_always_on_top():
    ui["win"].attributes("-topmost", ui["always_on_top_var"].get())

def buildui():
    ui["win"] = tk.Tk()
    ui["win"].title("Text Formatter")
    ui["win"].geometry("420x365")  # width x height in pixels


    modes_frame = ttk.LabelFrame(ui["win"], text="Modes")
    input_frame = ttk.Frame(ui["win"])
    output_frame = ttk.Frame(ui["win"])

    ui["mode_var"] = tk.StringVar(value=current_mode)
    for mode in mode_lengths:
        rb = ttk.Radiobutton(modes_frame, text=mode, variable=ui["mode_var"], value=mode, command=change_mode)
        rb.pack(anchor=tk.W)
    modes_frame.grid(row=0, column=0, padx=10, pady=10, sticky="n")

    ui["button"] = ttk.Button(modes_frame, text="Convert", command=click)
    ui["button"].pack(anchor=tk.CENTER, pady=10)

    ui["inlab"] = ttk.Label(input_frame, text="Input")
    ui["inbox"] = tk.Text(input_frame, wrap=tk.WORD, height=10, undo=True)
    ui["length_label"] = ttk.Label(input_frame, text="Line length: 0px")
    ui["inlab"].pack(anchor=tk.W)
    ui["inbox"].pack(fill=tk.BOTH, expand=True)
    ui["length_label"].pack(anchor=tk.W)
    input_frame.grid(row=0, column=1, padx=10, pady=10, sticky="nsew")

    ui["outlab"] = ttk.Label(output_frame, text="Output")
    ui["outbox"] = tk.Text(output_frame, state="disabled", wrap=tk.WORD, height=3, undo=True)
    ui["outlab"].pack(anchor=tk.W)
    ui["outbox"].pack(fill=tk.BOTH)
    output_frame.grid(row=1, column=0, columnspan=2, padx=10, pady=10, sticky="nsew")

    ui["win"].grid_rowconfigure(0, weight=1)
    ui["win"].grid_rowconfigure(1, weight=0)
    ui["win"].grid_columnconfigure(1, weight=1)

    ui["always_on_top_var"] = tk.BooleanVar(value=True)
    ui["always_on_top"] = ttk.Checkbutton(ui["win"], text="Always on Top", variable=ui["always_on_top_var"], command=toggle_always_on_top)
    ui["always_on_top"].grid(row=0, column=1, padx=10, pady=10, sticky="ne")
    if ui["always_on_top_var"].get():
        ui["win"].attributes("-topmost", True)

    ui["inbox"].bind("<KeyRelease>", update_line_length)
    ui["inbox"].bind("<Control-z>", lambda e: ui["inbox"].event_generate("<<Undo>>"))
    ui["inbox"].bind("<Control-y>", lambda e: ui["inbox"].event_generate("<<Redo>>"))

def main():
    buildui()
    ui["win"].mainloop()

if __name__ == "__main__":
    main()
