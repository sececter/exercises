unit libPole;

interface

type
	data = integer;
	pole = array[integer] of data;
	
function poleZeSouboru(jmenoS : string) : pole;
procedure vypisPole(p : pole);
function velikostPole(p : pole) : integer;

implementation

function poleZeSouboru(jmenoS : string) : pole;
var 
	userFile : text;
	d : data;
	i : integer;
	p : pole;
begin
assign(userFile, jmenoS);
reset(userFile);
i:=0;
repeat
	inc(i);
	readln(userFile, d);
	p[i]:=d;
until eof(userFile);
close(userFile);
inc(i);
p[i]:=0;
poleZeSouboru:=p;
end;

procedure vypisPole(p : pole);
var
	i : integer;
begin
i:=0;
while p[i+1]<>0 do begin
	inc(i);
	writeln(p[i]);
end;
end;

function velikostPole(p : pole) : integer;
var i : integer;
begin
i:=0;
while p[i+1]<>0 do inc(i);
velikostPole := i;
end;
end.
