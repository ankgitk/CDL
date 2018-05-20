"""
The NFA is a dictionary composed by:
    'state': [(char, new_state)]
"""
NFA = {
    'a': [('0', 'e'), ('1', 'e'), ('0', 'd'), ('1', 'd'), ('0', 'c'), ('0', 'b'), ('0', 'a')],
    'b': [('1', 'e'), ('0', 'c')],
    'c': [('1', 'b')],
    'd': [('0', 'e')],
    'e': []
}
 
STACK = []
SETS = []
abecedary = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
 
# This function allow to get all the chars that can be consumed in the NFA.
def get_voc():
    voc = set()
    for state in NFA:
        for c, q in NFA[state]:
            voc.add(c)
    if -1 in voc:
        voc.remove(-1)
    return list(voc)
 
def e_closure(states, consumable, set_e):
    for state in states:
        # When it is epsilon, you can always reach yourself, therefore you have to add it.
        if consumable == -1:
            set_e.add(state)
 
        if state in STACK:
            STACK.remove(state)
 
        state_NFA = NFA[state]
        for c, q in state_NFA:
			
            if c == str(consumable):
                if not q in set_e:
                    set_e.add(q)
                    STACK.append(q)
 
        e_closure(STACK, consumable, set_e)
    return set_e
 
voc = get_voc()
# Very important to set the first node!
first_node = 'a'
 
SETS.append(e_closure([first_node], -1, set()))
print SETS
for set_e in SETS:
    for char in voc:
        char_s = e_closure(set_e, char, set())
        set_res = e_closure(char_s, -1 , set())
        # print char, set_res
        if set_res not in SETS:
            SETS.append(set_res)
 
final_set = dict(zip(abecedary[:len(SETS)], SETS))
 
print "& States & " + " ".join(list(voc))

for key in abecedary[:len(final_set)]:
    print key, "& {", ", ".join(map(str, list(final_set[key]))), "} &",
    for char in voc:
        char_s = e_closure(final_set[key], char, set())
        set_res = e_closure(char_s, -1 , set())
        # print "set_res", set_res
        for key2 in final_set:
            if final_set[key2] == set_res:
                print key2, ("&" if char != voc[-1] else ""),
    print "\\"