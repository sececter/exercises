unit libStrom;

interface

const M = 1000;

type
	data = integer;
	pole = array[1..M] of data;
	uVrchol = ^Vrchol;
	Vrchol = record
		d : data;
		levy,pravy : uVrchol;
	end;
	Strom = object
		koren : uVrchol;
		constructor init;
		function vytvorVrchol(d : data) : uVrchol;
		procedure vlozDoStromu(var d : data; var vrch : uVrchol);
		procedure ulozDoPole(kor : uVrchol; var i : integer; var p : pole);
	end;
	
implementation

constructor Strom.init;
begin
new(koren);
koren:=nil;
end;

function Strom.vytvorVrchol(d : data) : uVrchol;
var pom : uVrchol;
begin
new(pom);
pom^.d := d;
pom^.levy := nil; pom^.pravy := nil;
vytvorVrchol:=pom;
end;

procedure Strom.vlozDoStromu(var d : data; var vrch : uVrchol);
begin
if koren = nil then koren := vytvorVrchol(d);
if koren^.d < d then vlozDoStromu(d,koren^.pravy)
else vlozDoStromu(d,koren^.levy);
end;

procedure Strom.ulozDoPole(kor : uVrchol; var i : integer; var p : pole);
begin
if kor<>nil then begin
ulozDoPole(kor^.levy,i,p);
inc(i);
p[i] := kor^.d;
inc(i);
ulozDoPole(kor^.pravy,i,p);
end;
end;
end.
