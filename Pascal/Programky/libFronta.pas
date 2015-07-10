unit libFronta;

interface
type
	data = integer;
	pole = array[integer] of data;
	uPrvek = ^Prvek;
	Prvek = record
		data : data;
		dalsi : uPrvek;
	end;
	Fronta = object
		hlava, konec : uPrvek;
		constructor vytvor;
		procedure vloz(var co : data);
		procedure vyjmi(var a : data);
		function prazdna : boolean;
	end;

implementation

constructor Fronta.vytvor;
begin
new(hlava);
konec := hlava;
hlava^.dalsi := nil;
end;

procedure Fronta.vloz(var co : data);
begin
konec^.data := co;
new(konec^.dalsi);
konec := konec^.dalsi;
konec^.dalsi := nil;
end;

procedure Fronta.vyjmi(var a : data);
var pom : uPrvek;
begin
pom := hlava;
hlava:=pom^.dalsi;
a:=pom^.data;
end;

function Fronta.prazdna : boolean;
begin
if hlava^.dalsi=nil then prazdna:=true
else prazdna := false;
end;
end.
