//x.
//x().
x(_).
x(1, 2.0, 'z', _, "moo").
//x[y].
x(1, 2.0, 'z', "moo")[y].
x([1,2,3]).
x([1|_]).
x([1|[]]).
x([1|[2|3]]).
x([1|[2|[3]]]).
x([1|[2,3]]).
x : true.
x() : true.
x(_) : true.
x(1, 2.0, 'z', _, "moo") : true.
x[y] : true.
x(1, 2.0, 'z', "moo")[y] : true.
x([1,2,3]) : true.
x([1|_]) : true.
x([1|[]]) : true.
x([1|[2|3]]) : true.
x([1|[2|[3]]]) : true.
x([1|[2,3]]) : true.
x([])[abacate] : true.
x[abacate] : L = 1 + 1.
x(K) : L = 1 + 1 && K = L/2.
