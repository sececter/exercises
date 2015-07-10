program quick1;

uses libZasob,libSeznam;

var 
	sez : seznam;

procedure quicksort;
var
	x,y : uPrvek;
	i,l,r : index;
	j,k : integer;
	zas : zasobnik;
begin
	zas.init; new(x); new(y);
	zas.vloz(1,sez.velikost);
	repeat
		zas.vyjmi(l,r);
		repeat
			x:=sez.nty(((l+r) div 2));
			sez.vlozZa(sez.nty(r),x^.data);
			sez.smaz(x);
			j:=0;
			k:=r;														{index pivota}
			for i:=l to r do begin
				y:=sez.nty(l);
				while j<k do begin
					if x^.data < y^.data then begin
						dec(k); inc(j);
						sez.vlozZa(sez.nty(k),y^.data);
						sez.smaz(y);
					end;
					y:=y^.dalsi;
				end;
			end;
			if k<r then zas.vloz(k,r);
			r := k;
		until l>=r;
		writeln;writeln;writeln;writeln;
		sez.vypsat;
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
