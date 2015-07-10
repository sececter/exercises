program binVkladani;

uses libSeznam;

var 
	puvodni, setrideny : Seznam;
	l,r,m,i : integer;
	x,y : uPrvek;

begin
puvodni.init; setrideny.init;
new(x); new(y);
puvodni := seznamZeSouboru('data');
i := 1;
while (y^.dalsi <> puvodni.konec) do begin
	y:=puvodni.vyjmiPrvni;
	l := 1; r := i-1;
	while (l<=r) do begin
		m := (l+r) div 2;
		x := setrideny.nty(m);
		if x^.data > y^.data then r:=m-1
		else l:=m+1;
	end;
	x := setrideny.nty(l);
	setrideny.vlozNamisto(x, y^.data);
	inc(i);
end;

setrideny.vypsat;

end.
