// définition des variables environnementales

let path = null;
let trail = null;
let pathIsDone = false;


let size = {};
size.width = 900;
size.height = 900;

let percentObstacles = 10;
let amount = 75;
// declaration de tout mes outils

// classe NODE
class Node
{
	constructor(_y, _x, _value)
	{
		this.value = _value;
		this.pos = new pos(_y, _x);
		this.gCost = 0;
		this.hCost = 0;
		this.parent = null;
	}
};

	Node.prototype.fCost = function()
	{
		return this.gCost + this.hCost;
	}


// fin de la classe NODE

class pos
{
	constructor(_y, _x)
	{
		this.y = _y;
		this.x = _x;
	}
}

// initialisation des variables environnementales

let canvas; 
let grid;
let render;

let dest;
let player = {};
player.cycleMax = 0;
player.cycle = player.cycleMax;
player.value = 2;
player.pathIndex = 0;

player.pos = new pos(1, 1);

let cycleTrailMax = player.cycleMax / 2;
let cycleTrail = cycleTrailMax;

let pathKey = {};
pathKey.keyCode = 80;
pathKey.letter = 'p';
let brushKey = {};
brushKey.keyCode = 66;
brushKey.letter = 'b';
let wallKey = {};
wallKey.keyCode = 87;
wallKey.letter = 'w';

let mode = pathKey.letter;

// taille de l'écran (le canvas)

function setupRender()
{
	let render = {};
	render.columnWidth = size.width / grid.x;
	render.columnHeight = size.height;

	render.lineWidth = size.width;
	render.lineHeight = size.height / grid.y;
	return render;
}

function setupGrid()
{
	let grid = {};
	grid.x = amount;
	grid.y = amount;

	grid.array = new Array(grid.y);
	for(let y = 0; y < grid.y; y++)
	{
		grid.array[y] = new Array(grid.x);
		for (let x = 0; x < grid.x; ++x)
		{
			grid.array[y][x] =  new Node(y, x, random(0, 100) < percentObstacles ? 1 : 0);
		}
	}
	
	grid.array[player.pos.y][player.pos.x].value = player.value;
	return grid;
}

function getNeighbours(_grid, currentNodePos)
{
	let list = new Array();
	if (currentNodePos.x - 1 >= 0 && _grid.array[currentNodePos.y][currentNodePos.x - 1].value == 0)
		list.push(_grid.array[currentNodePos.y][currentNodePos.x - 1]);
	if (currentNodePos.x + 1 < amount && _grid.array[currentNodePos.y][currentNodePos.x + 1].value == 0)
		list.push(_grid.array[currentNodePos.y][currentNodePos.x + 1]);
	if (currentNodePos.y - 1 >= 0 && _grid.array[currentNodePos.y - 1][currentNodePos.x].value == 0)
		list.push(_grid.array[currentNodePos.y - 1][currentNodePos.x]);
	if (currentNodePos.y + 1 < amount && _grid.array[currentNodePos.y + 1][currentNodePos.x].value == 0)
		list.push(_grid.array[currentNodePos.y + 1][currentNodePos.x]);

	return list;
}

function pathFinding(_grid, startPos, endPos)
{
	let openSet = new Array();
	let closedSet = new Array();
	openSet.push(_grid.array[startPos.y][startPos.x]);
	while (openSet.length > 0)
	{
		let current = openSet[0];
		for (let i = 1; i < openSet.length; ++i)
		{
			if (openSet[i].fCost() < current.fCost() || openSet[i].fCost() == current.fCost() && openSet[i].hCost < current.hCost)
				current = openSet[i];
		}
		openSet.splice(openSet.indexOf(current), 1);
		closedSet.push(current);
		if (current.pos.y == endPos.y && current.pos.x == endPos.x)
		{
			let _path = [];
			while (current.pos.y != startPos.y || current.pos.x != startPos.x)
			{
				_path.push(current);
				current = current.parent;
			}
			_path.push(current);
			reverse(_path);
			return _path; // reconstruire le chemin.
		}
		let neighbours = getNeighbours(_grid, current.pos);
		for (let i = 0; i < neighbours.length; ++i)
		{
			if ( closedSet.includes(neighbours[i]) )
				continue;
			let newMovementCostToNeighbour = current.gCost + dist(current.pos.x, current.pos.y, neighbours[i].pos.x, neighbours[i].pos.y);
			if (newMovementCostToNeighbour < neighbours[i].gCost || !openSet.includes(neighbours[i]))
			{
				neighbours[i].gCost = newMovementCostToNeighbour;
				neighbours[i].hCost = dist(neighbours[i].pos.x, neighbours[i].pos.y, endPos.x, endPos.y);
				neighbours[i].parent = current;
				if (!openSet.includes(neighbours[i]))
					openSet.push(neighbours[i]);
			}
		}
	}
}

function setup() 
{
	canvas = createCanvas(size.width, size.height);
	grid = setupGrid();
	render = setupRender();

}

function keyPressed()
{
	if (keyCode == brushKey.keyCode)
		mode = brushKey.letter;
	else if (keyCode == pathKey.keyCode)
		mode = pathKey.letter;
	else if (keyCode == wallKey.keyCode)
		mode = wallKey.letter;
}


function UpdatePlayerPos()
{
	if (path == null || trail == null)
		return;
	if (player.pathIndex == path.length && path != null)
	{
		path = null;
		player.pathIndex = 0;
		//clearTrail();
		reverse(trail);
		pathIsDone = true;
		return;
	}
	if (player.cycle > 0)
	{
		player.cycle--;
		return;
	}
//	grid.array[player.pos.y][player.pos.x].value = 0;
	trail.push(grid.array[player.pos.y][player.pos.x]);
	player.pos.y = path[player.pathIndex].pos.y;
	player.pos.x = path[player.pathIndex].pos.x;
	grid.array[player.pos.y][player.pos.x].value = player.value;
	player.pathIndex += 1;
	player.cycle = player.cycleMax;
}

function printPath()
{
	if (path == null || path.length == 0)
	{
		return;
	}
	strokeWeight(2);
	stroke(127,255,0);
	let offsetX = render.columnWidth / 2;
	let offsetY = render.lineHeight / 2;
	for(let i = 1; i < path.length; ++i)
	{
		if (path[i].value != player.value)
			line(path[i - 1].pos.x * render.columnWidth + offsetX, path[i - 1].pos.y * render.lineHeight + offsetY, path[i].pos.x * render.columnWidth + offsetX, path[i].pos.y * render.lineHeight + offsetY);
	}
}

function shortTrail()
{
	if (trail == null)
	{
		return;
	}
	if (cycleTrail > 0)
	{
		cycleTrail--;
		return;
	}
	grid.array[ trail[trail.length - 1].pos.y ][ trail[trail.length - 1].pos.x].value = 0;
	trail.pop();
	cycleTrail = cycleTrailMax;
	if (trail.length == 0)
	{
		trail = null;
		pathIsDone = false;
		grid.array[ player.pos.y ][ player.pos.x].value = player.value;
	}
}

function draw()
{
	background(225);
	printGrid();
	printContentGrid();
	UpdatePlayerPos();
	printPath();
	if (pathIsDone == true)
		shortTrail();
}


function mouseDragged()
{
	let mousePosX = floor( map(mouseX, 0, size.width, 0, grid.x) );
	let mousePosY = floor( map(mouseY, 0, size.height, 0, grid.y));
	if (mousePosX < 0 || mousePosX >= grid.x || mousePosY < 0 || mousePosY >= grid.y)
		return;
	if (mode == wallKey.letter && grid.array[mousePosY][mousePosX].value == 0)
		grid.array[mousePosY][mousePosX].value = 1;
	else if (mode == brushKey.letter && grid.array[mousePosY][mousePosX].value == 1)
		grid.array[mousePosY][mousePosX].value = 0;
}


function lookForPath(mousePosX, mousePosY)
{
	if (grid.array[mousePosY][mousePosX].value == 0)
	{
		if (trail != null && trail.length != 0)
		{
			pathIsDone = false;
			clearTrail();
		}
		path = null;
		player.pathIndex = 0;
		player.cycle = player.cycleMax;
		dest = new pos(mousePosY, mousePosX);
		path = pathFinding(grid, player.pos, dest);
		if (path != null)
			trail = new Array();
	}
}

function buildNewWall(mousePosX, mousePosY)
{
	if (grid.array[mousePosY][mousePosX].value == 0)
			grid.array[mousePosY][mousePosX].value = 1;
}

function destroyWall(mousePosX, mousePosY)
{	
	if (grid.array[mousePosY][mousePosX].value == 1)
		grid.array[mousePosY][mousePosX].value = 0;
}

function mousePressed()
{
	let mousePosX = floor( map(mouseX, 0, size.width,  0, grid.x) );
	let mousePosY = floor( map(mouseY, 0, size.height, 0, grid.y));
	if (mousePosX < 0 || mousePosX >= grid.x || mousePosY < 0 || mousePosY >= grid.y)
		return;
	if (mode == brushKey.letter)
		destroyWall(mousePosX, mousePosY);
	else if (mode == wallKey.letter)
		buildNewWall(mousePosX, mousePosY);
	else if (mode == pathKey.letter)
		lookForPath(mousePosX, mousePosY);

}

function clearTrail()
{
	for(let i = 0; i < trail.length; ++i)
		grid.array[trail[i].pos.y][trail[i].pos.x].value = 0;
	trail = null;
}


function printContentGrid()
{
	//let playerPrint = false;
    fill(0);
	strokeWeight(1);
	stroke(0);
    for(let y = 0; y < grid.y; ++y)
        for(let x = 0; x < grid.x; ++x)
		{
			if (grid.array[y][x].value == 1)
				rect(x * render.columnWidth, y * render.lineHeight, render.columnWidth, render.lineHeight);
			if (grid.array[y][x].value == player.value)
			{
				fill(255, 0, 0);
				stroke(255, 0, 0);
				rect(x * render.columnWidth, y * render.lineHeight, render.columnWidth, render.lineHeight);
				fill(0, 0, 0);
				stroke(0, 0, 0);
			}
		}
}

function printGrid()
{
	strokeWeight(1);
	stroke(0);
	for(let i = 0; i <= grid.y; ++i)
		line(0, render.lineHeight * i, render.lineWidth, render.lineHeight * i);
	for (let i = 0; i <= grid.x; ++i)
		line(render.columnWidth * i, 0, render.columnWidth * i, render.columnHeight);
}
