program radix;

uses libPole,libFronta;

const M = 10;

var
	A : pole;
	P : array[0..9] of Fronta;
	x,b,i,z,d,j,k : integer;
	
begin
A:=poleZeSouboru('data1');
z := 10; d:=1; j:=1;
for i:=0 to 9 do P[i].vytvor;

for i:=1 to M do begin
	for j:=1 to velikostPole(A) do begin
		x:=A[j];
		b:=((x div d) mod z);
		P[b].vloz(x);
	end;
	k:=1;
	for j:=0 to 9 do
		while not P[j].prazdna do begin P[j].vyjmi(A[k]); inc(k); end;
	d:=d*z;
end;
vypisPole(A);
end.
