sum=0
user=raw_input()
largo=len(user)
for i in range(4):
    sum+=ord(user[i])

print "USER",user

if (sum%2==0):
    print "Keygening..."
    if (largo >= 4):
        print "ADDITIONAL", hex(sum)
        password = (sum / 2) ^ 0x1234
        print "PASSWORD", password
else:
    print "Keygening... error"


