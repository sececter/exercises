program quick;

uses libZasob,libSeznam;

var 
	sez : seznam;
	x,y : uPrvek;

procedure quicksort;
var
	x,y,z : uPrvek;
	i,j,k,l,r : index;
	zas : zasobnik;
begin
	zas.init; new(x); new(y); new(z);
	zas.vloz(1,sez.velikost);
	repeat
		zas.vyjmi(l,r);
		i:=l; j:=r+1;
		x:=sez.nty(((l+r) div 2));
		sez.vlozZa(sez.nty(r),x^.data); sez.smaz(x);
		y:=sez.nty(l);
		while i<j do begin
			if y^.data < x^.data then begin inc(i); y:=y^.dalsi; end
			else begin dec(j); sez.vlozZa(x,y^.data); sez.smaz(y); end;
		end;
		if i < r then zas.vloz(i,r);
		r := j;
	until zas.prazdny;
end;

begin
sez.init;
sez := seznamZeSouboru('data');
quicksort;
sez.vypsat
end.
