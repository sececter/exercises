program bubble;

uses libObSeznam;

var
	sez : seznam;
	x,y : uPrvek;
begin
sez.init; new(x); new(y);
sez := seznamZeSouboru('data');
x := sez.hlava;
while x <> sez.konec do begin
	y := sez.konec;
	while y^.predchozi <> sez.hlava do begin
		y:=y^.predchozi;
		if y^.predchozi^.data > y^.data then sez.prohod(y, y^.predchozi);
	end;
	x := x^.dalsi;
end;

sez.vypsat;
end.
