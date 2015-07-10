program quick1;

uses libZasob,libSeznam;

var 
	sez : seznam;

procedure quicksort;
var
	x,y,z,p : uPrvek;
	i,l,r,q : index;
	zas : zasobnik;
begin
	zas.init; new(x); new(y); new(z);
	zas.vloz(1,sez.velikost);
	q:=1;
	repeat
		zas.vyjmi(l,r);
		repeat
			x:=sez.nty(l);
			y:=x^.dalsi;
			z:=sez.nty(r);
			while y<>z do begin
				if y^.data < x^.data then begin
					if q:=1 then writeln(y^.dalsi);
					p := y^.dalsi;
					sez.vlozNamisto(x,y^.data);
					sez.smaz(y);
					y:=p;
				end
				else y:=y^.dalsi;
			end;
			i:=sez.kolikaty(x);
			if i+1<r then zas.vloz(i+1,r);
			r := i-1;
		until l>=r;
	until zas.prazdny;
end;

begin
sez.init;
sez := seznamZeSouboru('data');
sez.vypsat;
writeln;writeln;writeln;
quicksort;
sez.vypsat;
end.
