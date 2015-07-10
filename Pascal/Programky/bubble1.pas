program bubble1;

uses libSeznam;

var
	sez : seznam;
	x,y : uPrvek;
begin
sez.init; new(x); new(y);
sez := seznamZeSouboru('data');
x := sez.hlava;
while x <> sez.konec do begin
	y := sez.hlava;
	while y^.dalsi <> nil do begin
		if y^.dalsi^.data < y^.data then sez.prohod(y, y^.dalsi);
		y:=y^.dalsi;
	end;
	x := x^.dalsi;
end;
sez.vypsat;
end.
