program inverze;

var inverzi : longint;

type
	data = integer;
	pole = array[1..200000] of data;

function velikostPole(p : pole) : integer;
var i : integer;
begin
i:=0;
while p[i+1]<>0 do inc(i);
velikostPole := i;
end;
	
function sloucit(var A,B : pole) : pole;
var
	C : pole;
	i,j,k : integer;
	m,n : integer;
begin
	m := velikostPole(A); n := velikostPole(B); i := 1; j := 1; k:=1;
	inverzi := inverzi + m;
	while (i<=m) and (j<=n) do begin
		if A[i] < B[j] then begin C[k] := A[i]; inc(k); inc(i); end
		else begin C[k] := B[j]; inc(k); inc(j); end;
	end;
	if i>m then while j<=n do begin C[k]:=B[j]; inc(k); inc(j); end;
	if j>n then while i<=m do begin C[k]:=A[i]; inc(k); inc(i); end;
	sloucit := C;
end;

function setriditSlucovanim(A : pole) : pole;
var
	B, C : pole;
	n,i : integer;
begin
n:=velikostPole(A);
if n>1 then begin
	for i:=1 to (n div 2) do B[i] := A[i];
	for i:=((n div 2)+1) to n do C[i-(n div 2)] := A[i];
	B := setriditSlucovanim(B); C := setriditSlucovanim(C);
	setriditSlucovanim:=sloucit(B,C);
end
else setriditSlucovanim := A;
end; 

var
	ar : pole;
	t : integer;
	n,i : longint;

begin
readln(t);
while(t > 0) do begin
	readln(n);
	inverzi := 0;
	for i:=0 to n-1 do readln(ar[i]);
	setriditSlucovanim(ar);
	writeln(inverzi);
end;
end.
