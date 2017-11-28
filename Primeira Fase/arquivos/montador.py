#///////////////////////////////////////////////////////////////////////
#/ Nome: Leonardo Ikeda                                 NUSP: 10262822//
#/ Nome: Henrique Cerquinho                             NUSP: 9793700///
#/ Nome: Henrique Suzuki                                NUSP: 10297626//
#///////////////////////////////////////////////////////////////////////

#!/usr/bin/python3

"""
Lê, na entrada padrão, um programa na linguagem de montagem da máquina
virtual e retorna um programa em C que executa este programa.

Uso:
    montador < entrada >
"""

from sys import argv

file = open("fibo.c", "w")
ip = 0
v = () # vetor de instruçoes
tabsim = {}

file.write("#include <stdio.h>\n")
file.write("#include " + '"arena.h"\n\n')
file.write("\nINSTR " + argv[1] + "[] = {\n")
with open(argv[1]) as f:
    for l in f:
        label = op = ""
        arg   = 0
        try:
            l = l[:l.index('#')]
        except:
            pass
        keys = l.split()
        if len(keys) > 0 and keys[0].endswith(":"):
            label = keys[0][:-1] # jogando fora o ':'
            tabsim[label]=ip
            keys.pop(0)
        if len(keys) > 0:
            op = keys.pop(0)
        if len(keys) > 0:
            arg = keys.pop(0)
            if arg in tabsim:
                arg = tabsim[arg]
        if op != "":
            file.write("\t{%s, %s},\n"%(op,arg))
        else:
            # nao pode atualizar o ip senao, se tiverem linhas em
            # branco, os endereços das labels saem errados
            ip -= 1
        ip += 1
file.write("};\n\n")

file.write("""
int main(int ac, char **av) {
    Maquina *maq = cria_maquina(""" + argv[1] + """);
    exec_maquina(maq, 1000);
    destroi_maquina(maq);
    return 0;
}""")
file.close()



# Local variables:
# mode: python
# End:
