import sys
import json
from typing import List, Dict
import math


class Variable:

    """
    L'objet Variable, peu de choses à developper dessus,
    son usage est principalement développé dans chaque fonction python
    """

    def __init__(self, varname: str, funcname: str, depth: int, offset: int, vartype: str, globl: bool = False, unreference: int = 0, size: list = None) -> None:
        self.varname = varname
        self.funcname = funcname
        self.depth = depth
        self.offset = offset
        self.vartype = vartype
        self.globl = globl
        self.unreference = unreference
        self.size = size


    def location(self):
        if self.globl:
            return f"{self.varname}(%rip)"
        else:
            return f"{self.offset}(%rbp)"
    

    def __repr__(self) -> str:
        return "v(" + self.varname + ", " + str(self.offset) + ", " + self.vartype + ")"


    def __str__(self) -> str:
        return self.__repr__()


class AssemblyFile:

    """
    L'objet qu'on utilise pour coder le code assembly
    """

    def __init__(self) -> None:
        
        self.own_asm = ""

        template = "template.s"
        if len(sys.argv) >= 3:
            template = sys.argv[2]
        
        with open(template, "r") as f:
            self.own_asm += f.read()

        self.current_section = "text"


    def add(self, content, **kwargs):
        
        if isinstance(content, list):
            for line in content:
                self.add(line, **kwargs)
            return

        indent = "\t"
        if "indent" in kwargs and not kwargs["indent"]:
            indent = ""

        self.own_asm += indent + content + "\n"


    def set_section(self, section):
        
        if section == self.current_section:
            return
        
        need_return = '\n' if self.own_asm != "" else ""
        self.add(f"{need_return}\t.{section}", indent=False)
        self.current_section = section



VARIABLES: List[Dict[str, Variable]] = [{}]
VARIABLE_OFFSET = 0
FUNCTIONS = {}

LOOP_IDENTIFIER = 0
ARRAY_IDENTIFIER = 0
IF_IDENTIFIER = 0
WHILE_IDENTIFIER = 0
WHILE_CURRENT = []

ARRAYS_SETUP = []

VAR_SZ = 8
COMMENT = '#'



def variable_id(name, funcname, depth):
    return name + "-" + funcname + "-" + str(depth)


def get_variable_object_via_json(element, funcname: str, depth: int) -> Variable:

    """
    Ici, on fournit un objet JSON, et le but est de dénicher la variable
    qui est derrière cet objet.

    Pour les variables basiques, c'est assez direct, mais mention quand même
    aux variables que l'on obtient en faisant *x, où l'on créé une fausse 
    variable temporaire, qui permet de pointer vers la bonne addresse.
    Dans le sens où l'on a jamais à proprement parler créé cette variable
    nous même. 
    """

    if element["action"] == "varget":
        return get_variable_object(element["name"], funcname, depth)
    
    print(element)
    if element["action"] == "rlop":
        
        if element["op"] == "*x":

            evaluate_expression(element["value"], funcname, depth)
            asm.add([
                f"{COMMENT} using evaluating address inside",
                ""
            ])

            pointed_obj = get_variable_object_via_json(element["value"], funcname, depth)
            return Variable(f"*{pointed_obj.varname}", pointed_obj.funcname, pointed_obj.depth, pointed_obj.offset, pointed_obj.vartype, pointed_obj.globl, pointed_obj.unreference + 1, pointed_obj.size[:-1])

    # CAREFUL HERE, VALUEGET COULD COME FROM SOMETHING ELSE, DONT KNOW WHAT THOUGH
    if element["action"] == "valueget":
        return get_variable_object_via_json(element["value"], funcname, depth)
    
    if element["action"] == "arrayget":
        pass
        


def get_variable_object(varname: str, funcname: str, depth: int) -> Variable:

    """
    Ici, pour obtenir l'objet correspondant à une variable
    à partir de son nom, de la fonction courante, et de la profondeur,
    on part de la profondeur donnée, et on itère depth en remontant les valeurs de
    VARIABLE[depth], puisque c'est la variable avec la plus basse profondeur
    qui correspond à nos critères qui est prioritaire.

    La profondeur 0 correspond aux variables globales, qui ne sont pas associées
    à une fonction, ce qui explique les deux if différents ci dessous
    """

    global VARIABLES
    depth_iterator = depth

    while depth_iterator >= 0:
        var_id = variable_id(varname, funcname, depth_iterator)
        if var_id in VARIABLES[depth_iterator]:
            return VARIABLES[depth_iterator][var_id]
        if varname in VARIABLES[depth_iterator]:
            return VARIABLES[depth_iterator][varname]
        depth_iterator -= 1
        
    raise Exception(f"Undefined Variable {var_id}/{varname}")


def get_variable_location(varname: str, funcname: str, depth: int):

    obj = get_variable_object(varname, funcname, depth)

    if obj.globl:
        return f"{obj.varname}(%rip)"
    else:
        return f"{obj.offset}(%rbp)"


def get_variable(varname: str, funcname: str, depth: int):

    location = get_variable_location(varname, funcname, depth)
    push_location(location, f"push variable {varname}")



def push_location(location: str, comment: str = "Default comment, variable expr :')"):

    asm.add([
        f"{COMMENT} {comment}",
        f"push {location}",
        ""
    ])


def push_pointer(location: str, comment: str = "Default comment, pushing pointer :')"):

    """
    Permet d'obtenir un pointeur vers une variable,
    donc du type &x;
    """

    asm.add([
        f"{COMMENT} {comment}",
        f"lea {location}, %rax",
        "push %rax",
        ""
    ])

def push_unreference(location: str, unref_count: int, comment: str = "Default comment, pushing unreferenced variable :')"):

    """
    Cela permet de déreferencer une variable, 
    donc opération du type *x;
    """

    asm.add([
        f"{COMMENT} {comment} unref_count: {unref_count}",
        f"mov {location}, %rax",
        ["mov (%rax), %rbx",
        "mov %rbx, %rax"] * unref_count,
        "push %rax",
        ""
    ])



def end_function_here():

    """
    Permet de terminer la fonction ici.
    """

    asm.add([
        "mov %rbp, %rsp",
        "pop %rbp",
        "ret",
        ""
    ])


def get_array_size(size: list):

    """
    Lire l'explication de define_array
    """

    if len(size) == 0:
        return 1
    sz = 0
    for el in size[::-1]:
        sz = el * (1 + sz)
    return sz + 1



def define_array(base_location: str, size: list):

    """
    Le but de la définition que l'on chosit des arrays est que 
    a[2][1] soit équivalent à *(*(a + 2) + 1)
    
    Pour cela, pour un tableau bi-dimensionnel, s'il est de taille
    2 puis 3 disons. La taille que l'on va allouer sera de 1 + 2 * (1 + 3 * 1) = 9
    (de la taille get_array_size juste au dessus). 

    a + 0 contient la valeur a + 1.
    
    a + 1 contient la valeur a + 3
    a + 2 contient la valeur a + 5

    a + 3 ne contient rien
    ...
    a + 8 ne contient rien

    Donc, pour résumer, la première valeur contient un pointeur vers un tableau
    de taille 2, dont chaque élément est un pointeur vers un autre tableau de taille 3.

    On a donc en soi, trois tableaux de tailles respectives, 1, puis 2, puis 2*3
    et de total 1 + 2 + 3 = 9, qui sont mis l'un à côté de l'autre en mémoire.
   
    L'entiéreté de la fonction consiste à mettre au bon endroit les pointeurs
    vers les bons tableaux, car il faut que l'on les initialise nous même.
    Toutes les expériences associés, pour obtenir les formules et le code 
    sont dans le fichier ex.py dans le même dossier.
    """

    global ARRAY_IDENTIFIER
    ARRAY_IDENTIFIER += 1

    asm.add([
        f"{COMMENT} initial values, n-dimensional",
        f"lea {base_location}, %r8",
        f"mov $1, %r9",
        "mov $0, %r10",
        ""
    ])

    for l in range(len(size)):

        asm.add([
            f"{COMMENT} looping for layer {l}",
            f"mov ${VAR_SZ}, %r11",
            "imul %r10, %r11",
            "mov %r8, %rax",
            "add %r11, %rax", # HERE
            "mov %rax, %r11",
            "",
            f"mov ${VAR_SZ}, %r12",
            f"imul ${size[l]}, %r12",
            "",
            "mov %r10, %r13",
            "add %r9, %r13",
            f"imul ${VAR_SZ}, %r13",
            "add %r8, %r13",
            "",
            "mov $0, %r15",
            ""
        ])

        asm.add(f"loop_n_dimensional_in_{l}_{ARRAY_IDENTIFIER}:", indent=False)

        asm.add([
            "cmp %r9, %r15",
            f"jge loop_n_dimensional_out_{l}_{ARRAY_IDENTIFIER}",
            "",
            "mov %r13, (%r11)",
            f"add ${VAR_SZ}, %r11", # HERE
            "add %r12, %r13",
            "",
            "add $1, %r15",
            f"jmp loop_n_dimensional_in_{l}_{ARRAY_IDENTIFIER}",
            ""
        ])

        asm.add(f"loop_n_dimensional_out_{l}_{ARRAY_IDENTIFIER}:", indent=False)

        asm.add([
            "",
            "add %r9, %r10",
            f"imul ${size[l]}, %r9",
            ""
        ])


def evaluate_scope(body, funcname, return_type, depth):

    """
    Sans doute la fonction la plus importante, permet d'évaluer 
    tous les statements à l'intérieur d'un scope. Un scope est un 
    regroupement de statements, souvent définis avec { stmt1; stmt2; etc; }

    On a donc, un peu de la même manière que evaluate_expression, pleins 
    de cas à traiter, qui sont sans doute plus complexes en général.
    """

    global VARIABLES, VARIABLE_OFFSET, LOOP_IDENTIFIER, IF_IDENTIFIER, WHILE_IDENTIFIER, WHILE_CURRENT

    if isinstance(body, dict):

        if "action" in body and body["action"] == "scope":

            """
            C'est un test assez simple qui permet d'éviter du code
            qui se répète, des fois l'abre qu'on explore peut être un peu
            décalé, en fonction d'où on appelle evaluate_scope, ceci permet 
            de descendre d'un echelon si besoin
            """
            evaluate_scope(body["body"], funcname, return_type, depth)
            return
        
        """
        Même chose ici, mais cela permet de monter d'un écheleon. Cela permet
        surtout de pouvoir appeler evaluate_scope(stmt1) tout simplement, 
        parce que evaluate_scope(s) s'attend à ce que s soit une liste initialement.
        """
        evaluate_scope([body], funcname, return_type, depth)
        return
    

    """
    Et ici, on peut traiter chacun des statements du scope.
    """
    for element in body:
        
        if element["action"] == "return":
            
            """
            Retour de fonction classique, on met en plus
            la valeur de retour attendu, si le return
            n'est pas un return; (ie sans valeur retour) dans %rax,
            ce qui permet ensuite de l'utiliser ou non après coup
            sans pour autant modifier la hauteur de la pile.

            Sinon, 
            int a = f(1);
            
            et
            f(1);

            n'auraient pas la même hauteur de pile en sortie, si on utilisait
            la pile plutôt qu'un registre.
            """

            if len(element["value"].keys()) != 0:
                evaluate_expression(element["value"], funcname, depth)
                asm.add([
                    f"{COMMENT} returning value",
                    f"pop %rax",
                    ""
                ])
            
            end_function_here()
            continue

        if element["action"] == "expr":

            """
            Ici, on nous dit qu'il faut simplement évaluer une valeur.
            On repart donc sur 'evaluate_expression(expr)'
            """

            evaluate_expression(element["value"], funcname, depth)
            continue

        if element["action"] == "vardef":

            """
            C'est ici que les variables sont définies, il faut donc
            les ajouter au dictionnaire courant. On garde toujours en 
            mémoire la profondeur que l'on a (égale à peu de choses près
            au nombre de brackets gauches ({) que l'on a ouverts sans encore
            qu'ils soient refermés). Et on définit la variable dans 
            VARIABLES[profondeur]. Voir get_variable_object pour plus de détails
            sur la profondeur

            Les variables simples prennent 64 bits de mémoire, et les tableaux
            autant que nécessaire, mais voir define_array pour plus de détails.

            Il faut donc faire baisser la taille de la pile pour avoir de la place
            pour la nouvelle variable.
            """

            varname = element['name']
            vartype = element['type']

            varsize = get_array_size(element["size"])

            var_id = variable_id(varname, funcname, depth)
            memory_var_size = VAR_SZ * varsize
            
            asm.add([
                f"{COMMENT} space for var {var_id}, type {vartype}",
                f"sub ${memory_var_size}, %rsp",
                ""
            ])

            VARIABLE_OFFSET += memory_var_size
            VARIABLES[depth][var_id] = Variable(varname, funcname, depth, -VARIABLE_OFFSET, vartype + "*" * len(element["size"]), size=element["size"])#element["size"])
            
            var_obj = VARIABLES[depth][var_id]
            location = var_obj.location()

            """
            Define array est une boucle qui fait n boucles 
            pour un tableau de dimension n, donc 0 boucles pour une 
            simple variable.
            """
            define_array(location, size=element["size"])

            if len(element["value"].keys()) > 0:

                """
                Ici c'est un peu de la triche, pour transformer les instructions du 
                genre int a = 5; en d'abord l'instruction int a; puis l'instruction
                a = 5;
                """

                # should be changed so that int c = 3; covers also global variables.
                rebuild_varset = {'action': 'varset', 'left_value': {'action': 'varget', 'name': varname}, 'op': '=', 'value': element['value']}
                evaluate_scope([rebuild_varset], funcname, return_type, depth)

            continue

        if element["action"] == "varset":

            print(VARIABLES)

            """
            Ce flag permet de savoir si l'on travaille avec des booléens
            """
            keep_one_bit_flag = False

            """
            On évalue d'abord la valeur que l'on veut insérer dans la variable
            à gauche.
            """
            evaluate_expression(element['value'], funcname, depth)

            """
            Puis le but est de récuperer l'addresse de la variable à gauche.
            On part du principe à l'instant final qu'il y a tout en haut de la pile 
            l'addresse de la variable, et juste en dessous la valeur que l'on veut
            assigner à cette variable.

            Il reste à distinguer les formes possibles de variable à gauche parmi
            a = 5; *(a + 2) = 5; a[3] = 5; et à appliquer les formules nécessaires
            pour obtenir l'addresse
            """
            left_val = element["left_value"]
            if left_val["action"] == "rlop" and left_val["op"] == "*x":
                evaluate_expression(left_val["value"], funcname, depth, True)
            
            elif left_val["action"] == "varget" and "name" in left_val:
                
                var_obj = get_variable_object(left_val["name"], funcname, depth)
                location = var_obj.location()
                print(var_obj.vartype, var_obj.varname)
                keep_one_bit_flag = (var_obj.vartype == "bool")

                asm.add([
                    f"{COMMENT} varset, pushing address",
                    f"lea {location}, %rax",
                    "push %rax",
                    ""
                ])  

            elif left_val["action"] == "arrayget":
                
                evaluate_expression(left_val["left_value"], funcname, depth)
                evaluate_expression(left_val["index"], funcname, depth)

                asm.add([
                    f"{COMMENT} computing location for array gettting",
                    f"pop %rbx {COMMENT} contains the index",
                    f"pop %rax {COMMENT} contains the array base pointer",
                    f"imul ${VAR_SZ}, %rbx",
                    f"add %rbx, %rax",
                    "push %rax",
                    ""
                ])

            else:
                print("NO WAY TO RETRIEVE LEFT-VAL FOUND", left_val)    

            asm.add([
                f"{COMMENT} dereference element",
                f"pop %rax {COMMENT} get back where to put",
                f"pop %rbx {COMMENT} get back evaluated value",
                ""
            ])

            """
            Si l'addresse pointe vers un boolean, on pose 1
            si la valeur est non nulle, et sinon 0
            """
            if keep_one_bit_flag:
                asm.add([
                    f"{COMMENT} keep_one_bit_flag"
                    "test %rbx, %rbx",
                    "setnz %bl",
                    "movzx %bl, %rbx",
                ])

            """
            Et cette simple ligne met la valeur dans l'addresse mémoire qui
            nous a été fournie.
            """
            asm.add([
                f"mov %rbx, (%rax)", 
                ""
            ])
            continue

        if element["action"] == "for":

            """
            Pour les boucles for, on doit faire un premier élément
            qui marque le début de la boucle, auquel on peut revenir 
            dès que la fin du scope intérieur est atteint.
            
            À chaque début de boucle, on test immédiatement la condition posée,
            et on part à l'indicateur de fin de boucle si elle n'est pas 
            respectée.

            Juste avant le marqueur de fin, on insère l'incrémentation 
            de la variable, où plus simplement n'importe quel statement
            qui a été fourni par l'utilisateur.
            """

            asm.add([
                f"{COMMENT} Starting loop", 
                ""
            ])

            """
            On rentre dans un nouveau scope, on ajoute donc un nouveau layer de variables
            """
            VARIABLES.append({})
            evaluate_scope([element["init"]], funcname, return_type, depth + 1)
            
            """
            Il faut que chaque boucle ait un identifiant unique, 
            pour que les 'jmp debut_boucle_26' ne puisse pas être confondus
            """
            LOOP_IDENTIFIER += 1
            starting_point = f"start_loop_{LOOP_IDENTIFIER}"
            end_point = f"end_loop_{LOOP_IDENTIFIER}"

            asm.add(f"{starting_point}:", indent=False)

            """
            C'est ici qu'on fait vérifier la condition d'entrée
            """
            asm.add(f"{COMMENT} checking condition")
            evaluate_expression(element["condition"], funcname, depth + 1)

            """
            Si elle n'est pas vérifiée, on part directement à la fin de 
            la boucle.
            """
            asm.add([
                "pop %rax",
                "test %rax, %rax",
                f"jz {end_point}",
                ""
            ])

            """
            Ensuite l'intérieur de la boucle est lu de manière classique
            """
            scope = element["body"]
            evaluate_scope(scope, funcname, return_type, depth + 1)
            evaluate_scope([element["update"]], funcname, return_type, depth + 1)

            """
            C'est ici qu'on repart au début de la boucle
            """
            asm.add([
                f"{COMMENT} back to start",
                f"jmp {starting_point}",
                ""
            ])

            asm.add(f"{end_point}:", indent=False)
            asm.add("")

            """
            Puis en quittant le scope intérieur, on retire 
            le layer supplémentaire de variable que l'on a rajouté
            """
            VARIABLES.pop()
            continue

        if element["action"] == "if":
            
            """
            Bon c'est un if, on a un premier endroit où jump pour rentrer
            dans le then, et un deuxième endroit où jump pour skip
            entièrement le then. Pas de else, ici, c'est au cas suivant
            que c'est traité.

            On rajoute encore un layer de variable, et on garde un identifiant
            unique pour ce IF.
            """

            IF_IDENTIFIER += 1
            VARIABLES.append({})

            if_point = f"if_point_{IF_IDENTIFIER}"
            if_past = f"if_past_{IF_IDENTIFIER}"
            
            evaluate_expression(element["condition"], funcname, depth + 1)


            asm.add([
                f"{COMMENT} checking if condition",
                "pop %rax",
                "test %rax, %rax",
                f"jnz {if_point}",
                f"jmp {if_past}",
                ""
            ])

            asm.add(f"{if_point}:", indent=False)

            scope_if = element["body"]
            evaluate_scope(scope_if, funcname, return_type, depth)
            
            asm.add([
                f"jmp {if_past}",
                ""
            ])
            asm.add(f"{if_past}:", indent=False)
            VARIABLES.pop()
            continue

        if element["action"] == "ifelse":
            
            """
            Vraiment la même chose que l'élement précédent, mais on peut en 
            plus passer au else lorsque l'on ne rentre pas dans le then.
            """

            IF_IDENTIFIER += 1
            VARIABLES.append({})

            if_point = f"if_point_{IF_IDENTIFIER}"
            if_else_point = f"if_else_{IF_IDENTIFIER}"
            if_past = f"if_past_{IF_IDENTIFIER}"
            
            evaluate_expression(element["condition"], funcname, depth + 1)

            asm.add([
                f"{COMMENT} checking ifelse condition",
                "pop %rax",
                "test %rax, %rax",
                f"jnz {if_point}",
                f"jmp {if_else_point}",
                ""
            ])

            asm.add(f"{if_point}:", indent=False)

            scope_if = element["body_if"]
            evaluate_scope(scope_if, funcname, return_type, depth)
            asm.add(f"jmp {if_past}")

            asm.add(f"{if_else_point}:", indent=False)

            scope_if = element["body_else"]
            evaluate_scope(scope_if, funcname, return_type, depth)
            asm.add(f"jmp {if_past}")

            asm.add(f"{if_past}:", indent=False)
            continue


        if element["action"] == "while":
            
            """
            Vraiment la même chose que le for, si ce n'est qu'il n'y 
            a pas d'incrémentation d'une variable à écrire nous, 
            même, simplement la condition au début de la boucle.

            Encore besoin d'un identifieur unique pour les while.
            Notamment important pour les break et continue plus tard.
            """

            VARIABLES.append({})

            WHILE_IDENTIFIER += 1
            WHILE_CURRENT.append(WHILE_IDENTIFIER)

            while_entry = f"while_entry_{WHILE_IDENTIFIER}"
            while_out = f"while_out_{WHILE_IDENTIFIER}"

            asm.add([
                f"{COMMENT} while loop",
                ""
            ])

            asm.add(f"{while_entry}:", indent=False)

            evaluate_expression(element["condition"], funcname, depth + 1)
            asm.add([
                f"{COMMENT} checking while condition",
                "pop %rax",
                "test %rax, %rax",
                f"jz {while_out}",
                ""
            ])

            evaluate_scope(element["body"], funcname, return_type, depth + 1)
            
            asm.add([
                f"{COMMENT} starting loop again",
                f"jmp {while_entry}",
                ""
            ])

            asm.add(f"{while_out}:", indent=False)

            WHILE_CURRENT.pop()
            VARIABLES.pop()
            continue

        if element["action"] == "scope":
            
            """
            Dans le cas où l'on a simplement for (...) { {int a = 2;} int b = 3; }, 
            ie des guillements imbriquées, ce qui est légal. Il suffit 
            donc de passer au noeud de prochaine profondeur dans l'arbre.
            """

            VARIABLES.append({})
            evaluate_scope(element["body"], funcname, return_type, depth + 1)
            VARIABLES.pop()
            continue


        if element["action"] == "keyword":
            
            """
            Ici on traite le cas des keyword continue et break.
            continue fait immédiatement jump au début du while courant
            et break fait imméditamenet jump à la fin du while courant
            """

            if element["keyword"] == "continue":

                asm.add([
                    f"{COMMENT} continue keyword",
                    f"jmp while_entry_{WHILE_CURRENT[-1]}",
                    ""
                ])
                continue

            if element["keyword"] == "break":

                asm.add([
                    f"{COMMENT} break keyword",
                    f"jmp while_out_{WHILE_CURRENT[-1]}",
                    ""
                ])
                continue

        """
        Si un statement n'a pas été traité.
        """
        print(element, "stmt")


        
def define_function(funcname, return_type, arguments, scope, added):

    """
    Ici notre but est donc d'écrire en assembleur l'équivalent d'une fonction

    On doit donc crééer pour chacune de ces fonctions un espace de variable
    que l'on va créer. On l'implémente avec une pile car en soi, une fois
    que le python a finit de lire une fonction, plus jamais ses variables
    ne seront utiles. Donc on peut ajouter un 'layer' à chaque nouvelle 
    fonction/chaque nouveau scope (voir la fonction evaluate_scope)
    et le retirer dès que la fonction est finie. 

    VARIABLES est donc cette pile, VARIABLE_OFFSET permet de savoir
    quel décalage total on a déjà utilisé par rapport à %rbp, le base pointer 
    de la fonction en cours, et donc de savoir à quel endroit allouer
    nos nouvelles variables.
    """

    global VARIABLES, VARIABLE_OFFSET, ARRAYS_SETUP
    
    current_depth = 1 # Voir la fonction evaluate scope
    VARIABLES.append({})

    if added is not None:
        print(added)
        evaluate_scope(added, funcname, return_type, current_depth)
    
    VARIABLE_OFFSET = 0

    """
    Ici, on prend toutes les définitions d'une fonction, en s'assurant
    que l'on est bien en section text, et en écrivant la base du début, 
    ie sauvegarder l'ancien base pointer (rbp) et set le nouveau rsp
    """

    asm.set_section("text")
    
    asm.add(f"{funcname}:", indent=False)
    asm.add([
        "push %rbp",
        "mov %rsp, %rbp",
        ""
    ])
    
    """
    Ici, pour chacun des tableaux que l'on a déclaré en global
    on assigne la structure attendue de tableau lorsque l'on rentre
    pour la première fois dans le main. Voir la fonction define_array
    pour plus de précisions.
    """
    if element['name'] == 'main':
        for location, size in ARRAYS_SETUP:
            define_array(location, size)

    """
    Ensuite, on récupère chacun des arguments de la fonction, qu'on trouve donc
    dans l'ordre à +16(%rbp) (car %(rbp) contient l'ancien %rbp, et +8(%rbp) contient
    un pointeur vers la ligne à laquelle reprendre après la fin de la fonction) puis 
    +24(%rbp), +32(%rbp) et ainsi de suite. Ne pas oublier de retourner les arguments
    car la pile a inversée l'ordre.
    """
    arg_count = len(arguments)
    for i, arg in enumerate(arguments):
        
        if arg["action"] != "arg":
            continue
        
        arg_type = arg["type"]
        arg_name = arg["name"]

        var_id = variable_id(arg_name, funcname, current_depth)
        VARIABLES[current_depth][var_id] = Variable(var_id, funcname, current_depth, 8 * (1 + (arg_count - i)), arg_type)

    """
    Et c'est ici qu'on évalue l'intérieur de la fonction
    """
    evaluate_scope(scope["body"], funcname, return_type, current_depth)
    
    """
    Ici, on s'assure que même sans return la fonction termine bien
    """
    end_function_here()

    """
    Puis on se débarasse du layer de variables inutiles maintenant
    que la fonction a été traitée.
    """
    VARIABLES.pop()




def evaluate_expression(expr, funcname, depth: int, pointer_arithmetic: bool = False):

    """
    Ici, il y a "simplement" pleins de cas à traiter, un par un. 
    
    On retourne le type supposé de l'expression évaluée, notamment
    pour savoir si l'on fait de l'arithmétique de pointeur:
    si pour c + d on a 'c' ou 'd' qui est détecté comme un pointeur,
    on multiplie l'autre pointeur par 8, pour décaler correctement sur la pile 

    Les expressions sont pour beaucoup des opérations binaires, qui 
    sont toutes du genre f(a, b). Pour cela, on évalue, a, on le pousse 
    sur la pile, on évalue b, puis on pop b puis on pop a, pour garder l'ordre
    et on applique les "operators" définis juste en dessous. 
    boolean_cast_rax et rbx servent à passer d'un entier à un booléen. (En
    gros 1 si a != 0 sinon 0). 
    """

    boolean_cast_rax = "test %rax, %rax\n\tsetnz %al\n\tmovzx %al, %rax\n\t"
    boolean_cast_rbx = "test %rbx, %rbx\n\tsetnz %bl\n\tmovzx %bl, %rbx\n\t"

    operators = {
        "+": "add %rax, %rbx",
        "-": "sub %rbx, %rax\n\tmov %rax, %rbx",
        "*": "imul %rax, %rbx",
        "/": "cqo\n\tidivq %rbx\n\tmov %rax, %rbx",
        "%": "xor %rdx, %rdx\n\tidivq %rbx\n\tmov %rdx, %rbx",
        "&&": f"{boolean_cast_rax}{boolean_cast_rbx}and %rax, %rbx",
        "||": f"{boolean_cast_rax}{boolean_cast_rbx}or %rax, %rbx",
        "&": "and %rax, %rbx",
        "|": "or %rax, %rbx",
        "<": "cmp %rbx, %rax\n\tsetl %bl\n\tmovzx %bl, %rbx",
        ">": "cmp %rax, %rbx\n\tsetl %bl\n\tmovzx %bl, %rbx",
        "<=": "cmp %rbx, %rax\n\tsetle %bl\n\tmovzx %bl, %rbx",
        ">=": "cmp %rax, %rbx\n\tsetle %bl\n\tmovzx %bl, %rbx",
        "==": "cmp %rax, %rbx\n\tsete %bl\n\tmovzx %bl, %rbx",
    }

    unioperators = {
        "!": f"{boolean_cast_rax}\n\tnot %rax\n\tand $1, %rax"
    }

    if expr["action"] == "lrop":

        if expr["op"] == "&x":

            """
            Permet de récupérer l'addresse pointée par une variable.
            Pour cela, on mémorise toutes les variables définies précédemment, 
            on trouve l'objet qui lui correspond (dans le python) et cet objet
            contient l'emplacement supposé de la variable en assembleur 
            (ainsi que d'autres données, voir 'class Variable:' en haut)
            
            Et il ne reste plus qu'à pousser le pointeur sur la pile pour ensuite
            l'utiliser: c'est la fonction push_pointer
            """

            left_val = expr["left_value"]
            var_obj: Variable = get_variable_object_via_json(left_val, funcname, depth)
            location = var_obj.location()

            push_pointer(location, "pushing pointer from expr")
            return var_obj.vartype + "*"
    
    if expr["action"] == "rlop":

        if expr["op"] == "*x":

            """
            Ici on prend un pointeur et on accède à sa valeur, il suffit donc d'évaluer
            expr dans notre *(expr), puis de retirer la référence.
            """

            _type = evaluate_expression(expr["value"], funcname, depth)
            
            asm.add([
                f"{COMMENT} dereferencing variable",
                "pop %rbx",
                "mov (%rbx), %rax",
                "push %rax",
                ""
            ])
            return _type[:-1] # On retire une étoile (le dernier caractère) car le type rendu possède une échelle de pointeur en moins



    if expr["action"] == "var":
        _type = get_variable(expr["name"], funcname, depth)
        return _type
    
    if expr["action"] == "valueget":

        """
        À peu de choses près, comme pour ce qui est du cas au dessus,
        une couche inutile du parseur pour nos besoins, donc on passe
        simplement au niveau suivant dans l'arbre qu'on explore actuellemnt
        """

        _type = evaluate_expression(expr["value"], funcname, depth)
        return _type

    if expr["action"] == "funcall":

        """
        Appel d'une fonction, si la fonction attend 6 arguments, on va
        pousser sur la pile arg1, puis arg2, arg3, arg4, arg5 et enfin arg6.
        La fonction part du principe qu'elle trouvera ses arguments en remontant
        la pile (l'ordre des arguments sera donc inversé)
        """

        arg_count = len(expr["args"])
        for arg in expr["args"]:
            evaluate_expression(arg, funcname, depth)

        asm.add([
            f"{COMMENT} function call",
            f"call {expr['name']}",
            f"add ${VAR_SZ * arg_count}, %rsp",
            "push %rax",
            ""
        ])

        # TODO HERE, ADD FUNCTION TYPE
        return "FIXING"
    
    if expr["action"] == "const":
        
        """
        Simplement une valeur constante, on peut passer au niveau suivant
        de l'arbre
        """
        
        _type = evaluate_expression(expr["value"], funcname, depth)
        return _type

    if expr["action"] == "int":

        """
        On pousse ici l'entier correspondant sur la pile
        """

        asm.add([
            f"{COMMENT} push const int",
            f"push ${expr['value']}",
            ""
        ])
        return "int"
 
    if expr["action"] == "varget":

        """
        Permet de récupérer la valeur d'une variable,
        il faut donc récupérer à partir du nom de la variable,
        et de la fonction dans laquelle on est, l'objet en python
        que l'on a créé durant son initialisation, et obtenir
        sa position dans la pile (ou sa position dans la mémoire globale
        si la variable est globale). On push ensuite sa valeur sur la pile
        """

        if "value" in expr:
            print("AAAAH")
            evaluate_expression(expr['value'], funcname, depth)
            return

        var = get_variable_object(expr["name"], funcname, depth)
        push_location(var.location(), "HEEEEEEEEELP")
        return var.vartype

    if expr["action"] == "litteral":

        """
        Contient des valeurs du type: int, bool, etc au prochain niveau
        """

        evaluate_expression(expr["value"], funcname, depth)
        return "int"

    if expr["action"] == "binop":

        """
        Expliqué tout en haut
        """
        
        _type1 = evaluate_expression(expr["v1"], funcname, depth)
        _type2 = evaluate_expression(expr["v2"], funcname, depth)


        """
        C'est ici que l'on multiplie par 8 la taille de l'élément
        droit ou gauche si l'on détecte que l'on travaille sur des pointeurs
        """

        if "*" in _type1:
            asm.add([
                f"{COMMENT} pointer arithmetic left",
                "pop %rbx",
                "pop %rax",
                f"mov ${VAR_SZ}, %rcx",
                "imul %rcx, %rbx",
                "push %rax",
                "push %rbx",
                ""
            ])
        if "*" in _type2:
            asm.add([
                f"{COMMENT} pointer arithmetic left",
                "pop %rbx",
                "pop %rax",
                f"mov ${VAR_SZ}, %rcx",
                "imul %rcx, %rax",
                "push %rax",
                "push %rbx",
                ""
            ])

        asm.add([
            f"{COMMENT} {expr['binop']}",
            "pop %rbx",
            "pop %rax",
            operators[expr['binop']],
            "push %rbx",
            ""
        ])

        if "*" in _type1:
            return _type1
        elif "*" in _type2:
            return _type2
        return _type1
    

    if expr["action"] == "bool":
        asm.add([
            f"{COMMENT} push const bool",
            f"push ${'1' if expr['value'] else '0'}",
            ""
        ])
        return "bool"

    if expr["action"] == "uniop":

        """
        Comme pour les opérateurs binaires, mais l'on a ici un seul
        opérateur
        """
        
        evaluate_expression(expr["value"], funcname, depth)
        current_uniop = expr["uniop"]

        asm.add([
            f"{COMMENT} uniop {current_uniop}",
            "pop %rax",
            unioperators[current_uniop],
            "push %rax",
            ""
        ])
        return "bool"

    if expr["action"] == "arrayget":

        """
        On accède ici à la valeur d'un array,
        il faut donc obtenir d'abord de quel array on parle, 
        ce que l'on fait en évaluant 'left_value'.

        Une fois cela fait, on évalue également l'index du tableau
        et on peut simplement pop les deux valeurs, pour les sommer 
        (en n'oubliant pas de multiplier l'index par 8 car on fait
        de l'arithmétique de pointeurs ici). Puis on push la somme
        """

        left_value = expr["left_value"]
        index = expr["index"]

        _type1 = evaluate_expression(left_value, funcname, depth)
        evaluate_expression(index, funcname, depth)

        asm.add([
            f"{COMMENT} array access",
            f"pop %rbx {COMMENT} index",
            f"pop %rax {COMMENT} array base pointer",
            "imul $8, %rbx",
            "add %rbx, %rax",
            "mov (%rax), %rbx",
            "push %rbx",
            ""
        ])
        return _type1[:-1]

    if expr["action"] == "sizeof":

        """
        On gère le cas des sizeof à part, en rentrant à la main
        la taille de chaque variable, pour ne pas considérer 'int'
        par exemple comme une variable.
        """

        possible_values = {
            'int': 8,
            'bool': 8
        }

        val = expr['value']
        to_push = VAR_SZ
        if val in possible_values:
            to_push = possible_values[val]

        asm.add([
            f"{COMMENT} pushing sizeof",
            f"push ${to_push}",
            ""
        ])
        return val

    print(expr, "expr") # Sert à print lorsqu'un type d'expression n'est pas traité

        



        




if __name__ == "__main__":

    if len(sys.argv) < 2:
        raise Exception("Missing a filename.json to open")

    with open(sys.argv[1], "r") as f:
        data = json.load(f)

    asm = AssemblyFile()

    to_add_when_calling = []
    for element in data:
        
        if element["action"] == "gvardef":

            """
            Pour les variables globales, deux choses à bien retenir:
            On ne peut faire la déclaration de quelque chose accessible partout
            que dans la section "bss", qui doit être en dehors du main.

            Cependant, l'allocation de ce qu'il y a dans les variables est fait
            dans la fonction main. ARRAY_SETUP sert à appliquer la structure de tableau
            choisie aux tableaux globaux. Voir le commentaire de define_array pour cela

            De la même manière, la variable to_add_when_calling mémorise les allocations
            du genre a = 5; qui même lorsqu'elles sont globales sont simplement executées
            dans le main.
            """
            
            arr_size = get_array_size(element["size"])
            
            asm.set_section("bss")
            asm.add([
                f".align {VAR_SZ}",
                f".type {element['name']}, @object",
                f".size {element['name']}, {VAR_SZ * arr_size}"
            ])
            asm.add(f"{element['name']}:", indent=False)
            asm.add(f".zero {VAR_SZ * arr_size}")

            varname = element['name']
            VARIABLES[0][varname] = Variable(varname, 'main', 0, 0, element['type'] + "*" * len(element['size']), True, 0)
            var_obj = VARIABLES[0][varname]

            ARRAYS_SETUP.append((var_obj.location(), element['size']))
            continue

        if element["action"] == "varset":
            to_add_when_calling.append(element)
            continue

        if element["action"] == "fundef":
            scope = element["body"]
            if element["name"] == "main":
                appened = to_add_when_calling
            else:
                appened = None
            define_function(element["name"], element["type"], element["args"], scope, appened)
            continue

    with open(sys.argv[1].replace(".json", ".s"), "w") as f:
        """
        C'est à ce moment ci qu'on passe d'une variable contenant 
        l'assembleur à un fichier
        """
        f.write(asm.own_asm)    



