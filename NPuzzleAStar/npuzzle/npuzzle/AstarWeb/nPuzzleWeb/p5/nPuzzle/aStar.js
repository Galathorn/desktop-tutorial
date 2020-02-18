let allNeighbours = new Array();


function getNeighbours(current)
{
	let neighbours = new Array();
	let n = null;
	if (current.empty.pos.y + 1 < current.size)
	{
		n = current.copyData();
		if (n == null)
			return null;
		n.defMove = "UP";
		n.Up();
		neighbours.push(n);
		if (!allNeighbours.includes(n))
			allNeighbours.push(n);
	}
	if (current.empty.pos.y - 1 >= 0)
	{
		n = current.copyData();
		if (n == null)
			return null;
		n.defMove = "DOWN";
		n.Down();
		neighbours.push(n);
		if (!allNeighbours.includes(n))
			allNeighbours.push(n);
	}
	if (current.empty.pos.x - 1 >= 0)
	{
		n = current.copyData();
		if (n == null)
			return null;
		n.defMove = "RIGHT";
		n.Right();
		neighbours.push(n);
		if (!allNeighbours.includes(n))
			allNeighbours.push(n);
	}
	if (current.empty.pos.x + 1 < current.size)
	{
		n = current.copyData();
		if (n == null)
			return null;
		n.defMove = "LEFT";
		n.Left();
		neighbours.push(n);
		if (!allNeighbours.includes(n))
			allNeighbours.push(n);
	}
	return neighbours;
}

function aStar(puzzle)
{
	let tmp = animationAreOn;
	animationAreOn = false;
	let path = new Array();
	let openSet = new Array();
	let closedSet = new Array();

	openSet.push(puzzle);
	let cycle = 0;
	while (openSet.length > 0)
	{
		cycle++;
	//	console.log("cycle : ", ++cycle);
		let current = openSet[0];
		for (let i = 0; i < openSet.length; ++i)
		{
			if (openSet[i].fCost() < current.fCost() || openSet[i].fCost() == current.fCost() && openSet[i].hCost() < current.hCost())
				current = openSet[i];
		}
		openSet.splice(openSet.indexOf(current), 1);
		closedSet.push(current);
		if (current.hCost() == 0) // si jamais on est à la solution
		{
			while (current.id > 1)
			{
				path.push(current.defMove);
				current = current.parent;
			}
			reverse(path);
			animationAreOn = tmp;
			console.log("cycle : ", cycle);
			console.log(path);
			for(let x = 0; x < allNeighbours.length; ++x)
				if (!stackNpuzzle.includes(allNeighbours[x]))
					stackNpuzzle.push(allNeighbours[x]);
			return path;
		}

		let neighbours = getNeighbours(current);
		if (neighbours == null)
		{
			console.log("Stack is empty.");
			for(let x = 0; x < allNeighbours.length; ++x)
				if (!stackNpuzzle.includes(allNeighbours[x]))
					stackNpuzzle.push(allNeighbours[x]);
			return null;
		}
		for (let i = 0; i < neighbours.length; ++i)
		{
			if (closedSet.includes(neighbours[i]))
				continue;
			let newMovementCostToNeighbour = current.gCost + abs(current.hCost() - neighbours[i].hCost());
			if (newMovementCostToNeighbour < neighbours[i].gCost || !openSet.includes(neighbours[i]))
			{
				neighbours[i].gCost = newMovementCostToNeighbour;
				neighbours[i].parent = current;
				if (!openSet.includes(neighbours[i]))
					openSet.push(neighbours[i]);
			}
		}
	}
	console.log("path n'est pas trouver, fin de a star");
	animationAreOn = tmp;
	return null;
}