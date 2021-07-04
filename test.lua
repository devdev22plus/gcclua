a = 11;
print("HI!!!!" .. string.format("%d", a));

function main()
	local firstNumber, secondNumber = dummyNumber();
	TestFunc("call from main dummyNumber is " .. string.format("first = %d, second = %d", firstNumber, secondNumber));

	local dummyData = dummyData();
	print(string.format("dummyData1: = %d, dummyData2: = %s", dummyData.dummy1, dummyData.dummy2 ))

	for k, v in ipairs(dummyList()) do
		print("k: " .. k .. ", v: " .. v);
	end
	for k, v in pairs(dummyList()) do
		print("# k: " .. k .. ", v: " .. v);
	end


	-- for k, v in ipairs(dummyMap()) do
	-- 	print("k: " .. k .. ", v: " .. v);
	-- end
	-- for k, v in pairs(dummyMap()) do
	-- 	print("# k: " .. k .. ", v: " .. v);
	-- end
	
	local dm = dummyMap();
	print(dm);
	print(#dm);
	print(type(dm));

	for k, v in pairs(dm) do
		print("# k: " .. k .. "(" .. type(k) .. ")" .. ", v: " .. v .. "(" .. type(v) .. ")");
	end

	print(dm["2"])

	-- for i = 1, dm do
	-- 	print(dm);
	-- end
	
	print("lua")

	startClock();
	local ee = 111;
	for i = 1, 100000 do
		ee = ee * i;
	end
	endClock();


end

