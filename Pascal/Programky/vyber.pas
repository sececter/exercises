program vyber;

uses libSeznam;

var
	sez : Seznam;
	x,y : uPrvek;
	i : integer;

begin
sez.init;
new(x); new(y);
sez := seznamZeSouboru('data');
i:=0;
while i <> sez.velikost do begin
	inc(i);
	x := sez.nty(i);
	y := sez.nty(i);
	while y <> sez.konec do begin
		if y^.data < x^.data then x:=y;
	y:=y^.dalsi;
	end;
	sez.prohod(sez.nty(i), x);
end;

sez.vypsat;

end.
