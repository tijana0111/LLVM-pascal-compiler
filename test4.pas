var
	i : integer = 0;
	j : integer = 0;
	b : boolean = false;
begin
	while i < 3 do:
		begin
			j := 0;
			while (j < 10 or b) do:
				begin
					j := j + 1;
					if (j mod 4 < 1) or b  then:
						write(i)
				end;
			i := i + 1
		end
		
end.