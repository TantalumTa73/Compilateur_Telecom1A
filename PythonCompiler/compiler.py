import sys
import json


VARIABLES = {}
LOCAL_VARIABLES = {}
VARIABLE_OFFSET = 0
FUNCTIONS = {}

FUNCTION_VARIABLE_DEFINITIONS = {}
FUNCTION_VARIABLE_SIZE = 0

SIZE = 8
COMMENT = "#"

CURRENT_ASM = ""
START_ASM = ""

CURRENT_SECTION = "text"
CODE_FRAGMENTS = {

}

def reduced_element(element):

    print("{", end="")
    for k in element.keys():
        if len(str(element[k])) > 10:
            print(f"{k}: 'Too long'", end=", ")
            continue
        print(f"{k}: '{element[k]}'", end=", ")
    print("}") 


def add_line(line = "", indent = True, start_asm = False):
    global CURRENT_ASM, START_ASM

    new_line = ('\t' if indent else '') + line + "\n"
    if not start_asm:
        CURRENT_ASM += new_line
    else:
        START_ASM += new_line


def set_section(section):

    global CURRENT_ASM, CURRENT_SECTION
    
    if CURRENT_SECTION == section:
        return
    
    need_return = '\n' if len(CURRENT_ASM) > 0 else ''
    add_line(f"{need_return}\t.{section}", indent=False)
    CURRENT_SECTION = section


def variable_identifier(varname: str, funcname: str):
    return varname + funcname



def set_variable(varname: str, funcname):


    varname_id = variable_identifier(varname, funcname)
    if varname_id in LOCAL_VARIABLES:
        add_line(f"# varset of var {varname_id}")
        add_line(f"pop -{LOCAL_VARIABLES[varname_id]}(%rbp)")
        add_line()
    else:
        add_line(f"pop %rax")
        add_line(f"mov %rax, {varname}(%rip)")
        add_line()


def get_variable_location(varname: str, funcname: str):

    if varname + funcname in LOCAL_VARIABLES:
        return f"-{LOCAL_VARIABLES[varname + funcname]}(%rbp)"
    else:
        return f"{varname}(%rip)"



def get_variable(varname: str, funcname: str):

    """
    push variable onto the stack
    """

    location = get_variable_location(varname, funcname)

    if varname + funcname in LOCAL_VARIABLES:
        add_line(f"{COMMENT} variable expr {varname + funcname}")
        add_line(f"push {location}")
    else:
        add_line(f"{COMMENT} variable expr glob {varname}")
        add_line(f"push {location}")
    add_line()


def evaluate_expression(expr, funcname):
    
    operators = {
        "plus": "add %rax, %rbx",
        "minus": "sub %rbx, %rax\n\tmov %rax, %rbx",
        "mult": "imul %rax, %rbx",
        "division": "cqo\n\tidivq %rbx\n\tmov %rax, %rbx",
        "modulo": "xor %rdx, %rdx\nidivq %rbx\nmov %rdx, %rbx",
    }
    
    if "action" in expr:

        if expr["action"] == "function":
            evaluate_expression(expr["expr"], funcname)      
            
            add_line(f"{COMMENT} calling function as expr")
            add_line(f"call {expr['name']}")
            add_line(f"add ${SIZE}, %rsp")
            add_line("push %rax")
            add_line()

    if "type" not in expr:
        return

    if expr["type"] == "operation":

        if expr["operator"] in operators.keys():
            
            evaluate_expression(expr["left"], funcname)
            evaluate_expression(expr["right"], funcname) # second argument should be pushed second

            add_line(f"{COMMENT} {expr['operator']}")         
            add_line("pop %rbx") # popping in reverse order
            add_line("pop %rax")

            add_line(operators[expr["operator"]])

            add_line("push %rbx")
            add_line("")

        if expr["operator"] == "uminus":

            evaluate_expression(expr["right"], funcname)

            add_line(f"{COMMENT} uminus")
            add_line("pop %rax")
            add_line("neg %rax")
            add_line("push %rax")
            add_line("")
        
        return

    if expr["type"] == "cst":

        add_line(f"{COMMENT} constant expr")
        add_line(f"push ${expr['value']}")
        add_line("")
        return

    if expr["type"] == "var":
        get_variable(expr["name"], funcname)
        return
    
    if expr["type"] == "parenthesis":
        evaluate_expression(expr["inner"], funcname)
        return
    
    reduced_element(expr)


def end_function_here():

    global LOCAL_VARIABLES

    add_line("mov %rbp, %rsp")
    add_line("pop %rbp")
    add_line("ret")
    add_line()



def define_function(funcname, body, arg):

    global LOCAL_VARIABLES, VARIABLE_OFFSET, FUNCTION_VARIABLE_SIZE
    FUNCTION_VARIABLE_SIZE = 0

    set_section("text")
    add_line(f"{funcname}:", indent=False)
    add_line("push %rbp")
    add_line("mov %rsp, %rbp")
    add_line()

    FUNCTION_VARIABLE_SIZE += SIZE
    LOCAL_VARIABLES[arg + funcname] = FUNCTION_VARIABLE_SIZE

    add_line(f"{COMMENT} get argument, variable {arg + funcname}")
    add_line(f"mov {2*SIZE}(%rbp), %rax")
    add_line(f"mov %rax, -{LOCAL_VARIABLES[arg + funcname]}(%rbp)")
    add_line(f"sub ${SIZE}, %rsp")
    add_line()
    
    for element in body:

        if "action" in element:

            if element["action"] == "return":
                evaluate_expression(element["expr"], funcname)
                add_line(f"{COMMENT} return")
                add_line("pop %rax")
                add_line()

                end_function_here()
                break
        
            if element["action"] == "gvardef":
                add_line(f"{COMMENT} space for var {element['name'] + funcname}")
                add_line(f"sub ${SIZE}, %rsp")
                FUNCTION_VARIABLE_SIZE += SIZE
                LOCAL_VARIABLES[element["name"] + funcname] = FUNCTION_VARIABLE_SIZE
                add_line()
                continue

            if element["action"] == "varset":
                evaluate_expression(element["expr"], funcname)
                set_variable(element['name'], funcname)
                continue

            if element["action"] == "function":

                if element["name"] != "read":
                    evaluate_expression(element["expr"], funcname)

                if element["name"] == "print":
                    add_line("# print value")
                    add_line("call print")
                    add_line()
                    continue

                if element["name"] == "read":
                    add_line("# read value")
                    add_line("call scan")
                    location = get_variable_location(element['expr']['name'], funcname)
                    add_line(f"mov %rax, {location}")
                    add_line()
                    continue

                add_line("# function call, no varset")
                add_line(f"call {element['name']}")
                add_line(f"add ${SIZE}, %rsp")      
                add_line()          


    add_line(f"{COMMENT} just in case final return")
    add_line("mov $0, %rax") 

    end_function_here()







if __name__ == "__main__":

    if len(sys.argv) < 2:
        raise Exception("Missing a filename.json to open")

    with open(sys.argv[1], "r") as f:
        data = json.load(f)

    template = "template.s"
    if len(sys.argv) >= 3:
        template = sys.argv[2]

    with open(template, "r") as f:
        CURRENT_ASM = f.read()


    to_add_when_calling = []
    

    for element in data:
        
        if element["action"] == "gvardef":
            set_section("bss")
            add_line(f".align {SIZE}")
            add_line(f".type {element['name']}, @object")
            add_line(f".size {element['name']}, {SIZE}")
            add_line(f"{element['name']}:", indent=False)
            add_line(f".zero {SIZE}")
            continue

        if element["action"] == "varset":
            to_add_when_calling.append(element) 
            continue

        if element["action"] == "gfundef":
            body = element["body"]
            if element["name"] == "main":
                body = to_add_when_calling + body
            define_function(element["name"], body, element["arg"])
            continue

    with open(sys.argv[1].replace(".json", ".s"), "w") as f:
        f.write(CURRENT_ASM)