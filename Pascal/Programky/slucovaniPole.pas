program slucovaniPole;

uses libPole;

var
	A : pole;
	
function sloucit(var A,B : pole) : pole;
var
	C : pole;
	i,j,k : integer;
	m,n : integer;
begin
	m := velikostPole(A); n := velikostPole(B); i := 1; j := 1; k:=1;
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

begin
A:=poleZeSouboru('data');
A:=setriditSlucovanim(A);
vypisPole(A);
end.
