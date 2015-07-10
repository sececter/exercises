unit libZasob;

interface

const M = 1000;

type 
	index = 1..1000;

	zasobnik = object
		z : array[1..M] of record l,r : index end;
		vrch : 0..M;
		constructor init;
		procedure vloz(i,j : index);
		procedure vyjmi(var i,j : index);
		function prazdny : boolean;
	end;

implementation
{------------------------metody zasobniku------------------------------}

constructor zasobnik.init;
begin
	vrch := 0;
end;

procedure zasobnik.vloz(i,j : index);
begin
	inc(vrch);
	z[vrch].l := i; z[vrch].r := j;
end;

procedure zasobnik.vyjmi(var i,j : index);
begin
	i := z[vrch].l; j := z[vrch].r;
	dec(vrch);
end;

function zasobnik.prazdny : boolean;
begin
	if vrch = 0 then prazdny := true
	else prazdny := false;
end;

end.
