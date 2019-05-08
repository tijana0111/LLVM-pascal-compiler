var
	a : boolean = false;
	b : boolean = true;
	c : boolean;
begin
	c := not a;
	write(c);
	write(a or (b and 3 > 5))
end.