require "physics"
require "GameLoop"

stage = display.getCurrentStage( )

gameLoop = GameLoop:new()
gameLoop:start()

physics.setDrawMode( "hybrid" )
--physics.setDrawMode( "normal" )
--physics.setDrawMode( "debug" )
physics.start( )
physics.setGravity( 0, 9.8 )
physics.setPositionIterations( 10 )

function getWall(w, h)
	local wall = display.newRect(0, 0, w, h)
	physics.addBody( wall, "static", {density=2, friction=0.8, bounce=0.1} )
	return wall
end

function getPlayer()
	local rect = display.newRect( 0, 0, 30, 60 )
	physics.addBody( rect, "dynamic", {density=2, friction=0.8, bounce=0.1} )
	-- move player without being affected by outside forces
	rect.isFixedRotation = true
	return rect
end

function getButton()
	local rect = display.newRect( 260, 30, 60, 60 )
	rect:setFillColor( 255, 0, 0 )
	return rect
end

function getBox()
	local rect = display.newRect( 0, 0, 30, 30 )
	physics.addBody( rect, "dynamic", {density=0.8, friction=0.7, bounce=0.2} )
	return rect
end


local floor = getWall(1400, 30)
floor.y = stage.height

local wall1 = getWall(30, 700)
local wall2 = getWall(30, 700)
wall2.x = stage.width - 15

local player = getPlayer()
player.direction = nil -- "right", "left"
player.speed = 2.4

function player:tick( millisecondsPassed )
	--print( "millisecondsPassed:", millisecondsPassed )
	if self.direction == nil then return false end

	if self.direction == "right" then
		self.x = self.x + self.speed
	end

	if self.direction == "left" then
		self.x = self.x - self.speed
	end
end

function player:moveRight()
	self.direction = "right"
end

function player:moveLeft()
	self.direction = "left"
end

function player:stopMoving()
	self.direction = nil
end

function player:jumpRight()
	self:applyLinearImpulse(300, 300, self.x, self.y)
end


gameLoop:addLoop(player)

local moveLeftButton = getButton()
function moveLeftButton:touch( event )
	if event.phase == "began" then
		player:moveLeft()
		return true
	elseif event.phase == "ended" then
		player:stopMoving()
		return true
	end
end

local jumpButton = getButton()
function jumpButton:touch( event )
	if event.phase == "ended" then
		player:jumpRight()
		return true
	end
end

local moveRightButton = getButton()
function moveRightButton:touch( event )
	if event.phase == "began" then
		player:moveRight()
		return true
	elseif event.phase == "ended" then
		player:stopMoving()
		return true
	end
end

moveLeftButton:addEventListener( "touch", moveLeftButton )
moveRightButton:addEventListener( "touch", moveRightButton )
jumpButton:addEventListener( "touch", jumpButton )

jumpButton.x = moveRightButton.x + moveRightButton.width + 12
moveRightButton.x = jumpButton.x + jumpButton.width + 12

local box1 = getBox()
box1.x = 60