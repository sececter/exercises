program vkladani;

uses libSeznam;

var 
	puvodni,setrideny : Seznam;
	x,y : uPrvek;
	
begin
puvodni.init; setrideny.init;
puvodni := seznamZeSouboru('data');
new(x); new(y);
while y^.dalsi<>puvodni.konec do begin
	y := puvodni.vyjmiPrvni;
	x := setrideny.hlava;
	while (y^.data > x^.data) and (x^.dalsi<>nil) do x:=x^.dalsi;
	setrideny.vlozNamisto(x, y^.data)
end;

setrideny.vypsat;

end.
