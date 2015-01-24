/* Test a single belief without parms and it with annotations too */
r[y].
r()[y]. /* This is the same as line 2 */
l[house, green].
correct[house[green[half]]].
k[X].
/* not sure about theses. Should it be blocked?
        My vote is to yes, it should be blocked. The explanation is
        because "blablabla", 'b', 123 and 'b' 'l' 'a' cant have meta
        information.
        Othe point is that X = ["blabla", 123] must be allowed.
        So we have a conflict!
        I'll wait for more tests to change the grammar.
    XXX TODO For know keep it as allowed.
 */
x["blalbla"].
x['r'].
x['b' 'l' 'a'].
x[123].
x[0.5].
/* it fails */
//X[y].
