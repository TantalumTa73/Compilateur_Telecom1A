import sys
import json


VARIABLES = {}
LOCAL_VARIABLES = {}
VARIABLE_OFFSET = 0
FUNCTIONS = {}

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


def evaluate_expression(expr):
    
    operators = {
        "plus": "add %rax, %rbx",
        "minus": "sub %rbx, %rax\n\tmov %rax, %rbx",
        "mult": "imul %rax, %rbx",
        "division": "cqo\n\tidivq %rbx\n\tmov %rax, %rbx",
        "modulo": "xor %rdx, %rdx\nidivq %rbx\nmov %rdx, %rbx",
    }
    
    if "action" in expr:

        if expr["action"] == "function":
            evaluate_expression(expr["expr"])      
            
            add_line("push %rax")
            add_line(f"call {expr['name']}")
            add_line(f"add ${SIZE}, %rsp")
            add_line("push %rax")
            add_line()

    if "type" not in expr:
        # reduced_element(expr)
        # print("----")
        return

    if expr["type"] == "operation":

        if expr["operator"] in operators.keys():
            
            evaluate_expression(expr["left"])
            evaluate_expression(expr["right"]) # second argument should be pushed first

            add_line(f"{COMMENT} {expr['operator']}")         
            add_line("pop %rbx")
            add_line("pop %rax")

            add_line(operators[expr["operator"]])

            add_line("push %rbx")
            add_line("")

        if expr["operator"] == "uminus":

            evaluate_expression(expr["right"])

            add_line(f"{COMMENT} uminus")
            add_line("pop %rax")
            add_line("neg %rax")
            add_line("push %rax")
            add_line("")
        
        return

    if expr["type"] == "cst":

        add_line(f"{COMMENT} constant")
        add_line(f"push ${expr['value']}")
        add_line("")
        return

    if expr["type"] == "var":

        add_line(f"{COMMENT} variable expr")

        # print(LOCAL_VARIABLES)
        if expr['name'] in LOCAL_VARIABLES:
            add_line(f"push -{LOCAL_VARIABLES[expr['name']]}(%rbp)")
        else:
            add_line(f"push [{expr['name']}]")

        add_line()
        return
    
    if expr["type"] == "parenthesis":
        evaluate_expression(expr["inner"])
        return
    
    reduced_element(expr)


def end_function_here():

    global LOCAL_VARIABLES

    add_line(f"{COMMENT} removing all local variable")
    add_line(f"add ${len(LOCAL_VARIABLES.keys()) * SIZE}, %rsp")

    add_line("mov %rbp, %rsp")
    add_line("pop %rbp")
    add_line("ret")
    add_line()



def define_function(funcname, body, arg):

    global LOCAL_VARIABLES, VARIABLE_OFFSET
    LOCAL_VARIABLES = {}

    set_section("text")
    add_line(f"{funcname}:", indent=False)
    add_line("push %rbp")
    add_line("mov %rsp, %rbp")
    add_line()

    LOCAL_VARIABLES[arg] = SIZE
    VARIABLE_OFFSET += SIZE

    add_line(f"{COMMENT} get argument, variable {arg}")
    add_line(f"mov {2*SIZE}(%rbp), %rax")
    add_line(f"mov %rax, -{LOCAL_VARIABLES[arg]}(%rbp)")
    add_line(f"sub ${SIZE}, %rsp")
    add_line()
    
    for element in body:

        if "action" in element:

            if element["action"] == "return":
                evaluate_expression(element["expr"])
                add_line(f"{COMMENT} return")
                add_line("pop %rax")
                add_line()

                end_function_here()
                break
        
            if element["action"] == "gvardef":
                add_line(f"{COMMENT} space for var {element['name']}")
                add_line(f"sub ${SIZE}, %rsp")
                VARIABLE_OFFSET += SIZE
                LOCAL_VARIABLES[element["name"]] = VARIABLE_OFFSET
                add_line()
                continue

            if element["action"] == "varset":
                evaluate_expression(element["expr"])
                add_line(f"{COMMENT} varset {element['name']}")
                add_line(f"pop -{LOCAL_VARIABLES[element['name']]}(%rbp)")
                add_line()
                continue
            # if element[""]

            if element["action"] == "function":

                # print(element)
                if element["name"] != "read":
                    evaluate_expression(element["expr"])

                if element["name"] == "print":
                    add_line("# print value")
                    add_line("call print")
                    add_line()

                if element["name"] == "read":
                    add_line("# read value")
                    add_line("call scan")
                    add_line("push %rax")
                    add_line(f"pop -{LOCAL_VARIABLES[element['expr']['name']]}(%rbp)")
                    add_line()


                # add_line(f"{COMMENT} printf")

                # add_line("pop %rsi")
                # # add_line("mov $-2, %rsi")
                # if VARIABLE_OFFSET % 16 != 0:
                #     add_line("sub $8, %rsp")

                # add_line("lea int_fmt(%rip), %rdi")
                # add_line("mov $0, %rax")
                # add_line("call printf")
                # add_line("xor %rax, %rax")

                # if VARIABLE_OFFSET % 16 != 0:
                #     add_line("add $8, %rsp")

                # add_line()





        # reduced_element(element)

        # if "expr" in element:
        #     evaluate_expression(element["expr"])

    add_line(f"{COMMENT} just in case final return")
    add_line("mov $0, %rax") 

    end_function_here()







if __name__ == "__main__":

    if len(sys.argv) < 2:
        raise Exception("Missing a filename.json to open")

    # print(sys.argv[1])
    with open(sys.argv[1], "r") as f:
        data = json.load(f)

    with open("template.s", "r") as f:
        CURRENT_ASM = f.read()

    # set_section("data")
    # add_line("int_fmt:", indent=False)
    # add_line('.string "%d\\n"')

    # set_section("text")
    # add_line(".globl main")


    for element in data:
        
        # reduced_element(element)
        if element["action"] == "gvardef":
            set_section("bss")
            CURRENT_ASM += f"\t{element['name']}: .quad\n"

        if element["action"] == "gvarset":
            pass

        if element["action"] == "gfundef":
            define_function(element["name"], element["body"], element["arg"])


    # add_line("", indent=True, start_asm=True)
    # add_line("push $0", indent=True, start_asm=True)
    # add_line("call main", indent=True, start_asm=True)
    # add_line("", indent=True, start_asm=True)
    # add_line("mov $60, %rax", indent=True, start_asm=True)
    # add_line("xor %rdi, %rdi", indent=True, start_asm=True)
    # add_line("syscall", indent=True, start_asm=True)


    # CURRENT_ASM += START_ASM
    # print(CURRENT_ASM)

    with open("out.s", "w") as f:
        f.write(CURRENT_ASM)