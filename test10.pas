var
	i : integer = 0;
	j : integer = 0;
begin
	while i < 10 do:
		begin
			j := 0;
			while j < 10 do:
				begin
					write(i);
					write(j);
					j := j + 1
				end;
			
			i := i + 1
		end
		
end.
