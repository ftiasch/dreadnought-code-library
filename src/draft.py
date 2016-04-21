F = open('table.in').readlines()
Q = [s.split()[0] for s in F]
for s in Q:
    print '%\\section{' + s + '}'
    print '%\\inputminted{cpp}{src/' + s + '.cpp}'
    print ''

