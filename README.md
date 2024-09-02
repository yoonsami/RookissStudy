local SCREEN_WIDTH = 1920  -- 가로비율
local SCREEN_HIGHT = 1080  -- 세로비율
local TOLERANCE = 5	    -- 마우스 이동속도 1~4 적당 높으면 정확도 떨어져서 칼퇴 실패율 높아짐
local INPUT_DELAY = 8     -- 동작 사이사이 딜레이


local function PressAndReleaseMouseButton(button)
	PressMouseButton(button)
	Sleep(INPUT_DELAY)
	ReleaseMouseButton(button)
	Sleep(INPUT_DELAY)
end -- end function


local function PressAndReleaseKey(keyname)
	PressKey(keyname)
	Sleep(INPUT_DELAY)
	ReleaseKey(keyname)
	Sleep(INPUT_DELAY)
end -- end function

local function GetCurrentPixel()
	local coord_x_64K, coord_y_64K = GetMousePosition()
	Sleep(1)
	local coord_x_pixel = math.floor((coord_x_64K + (0.5 + 2^-16)) * (SCREEN_WIDTH - 1) / 65535)
	local coord_y_pixel = math.floor((coord_y_64K + (0.5 + 2^-16)) * (SCREEN_HIGHT - 1) / 65535)
	return coord_x_pixel, coord_y_pixel
end -- end function


local function MoveMousePixel(target_x_pixel,target_y_pixel)

local current_x_pixel, current_y_pixel, x, y

local maximum_cnt = SCREEN_WIDTH


while true do

current_x_pixel, current_y_pixel = GetCurrentPixel()



if current_x_pixel - target_x_pixel > TOLERANCE then

x = -1

elseif target_x_pixel- current_x_pixel > TOLERANCE then

x = 1

else

x = 0

end



if current_y_pixel - target_y_pixel > TOLERANCE then

y = -1

elseif target_y_pixel - current_y_pixel > TOLERANCE then

y = 1

else

y = 0

end



MoveMouseRelative(x * (TOLERANCE+1) , y * (TOLERANCE+1) )



maximum_cnt = maximum_cnt - 1


if maximum_cnt <0 or (x== 0 and y == 0) then

	 break

end

end


Sleep(FUNCTION_DELAY)

end

local function Retreat(x,y,num)
	MoveMousePixel(x,y,num)
end --end function



--------------------------------설정 변경 ---------------------------------
																		
function OnEvent(event, arg)	

	if event == "MOUSE_BUTTON_RELEASED" and arg == 6 then	--
             PressAndReleaseKey("escape")
             PressAndReleaseKey("escape")
	end	



end
