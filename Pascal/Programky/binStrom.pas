program binStrom;

uses libPole,libStrom;

var
	A : libpole.pole;
	B : libstrom.pole;
	i,n : integer;
	str : strom;

begin
A := poleZeSouboru('data');
n := velikostPole(A);
str.init;
for i:=1 to n do str.vlozDoStromu(A[i],str.koren);
i:=0;
str.ulozDoPole(str.koren, i, B);
end.
