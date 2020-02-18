
function setupRender()
{
	render = {};
	render.spaceX = env.width * 0.025;
	render.spaceY = env.height * 0.025;
	render.squareWidth = (env.width - render.spaceX) / env.squareSize;
	render.squareHeight = (env.height - render.spaceY) / env.squareSize;
}

function setupNpuzzle()
{
	if (env.squareSize < 2)
	{
		alert("Invalid Size");
		return;
	}
	npuzzle = new nPuzzle(env.squareSize);
	npuzzle.grid = npuzzle.createGrid(npuzzle.size);
	npuzzle.fillGrid(npuzzle.grid, npuzzle.size);
	npuzzle.empty = npuzzle.fillEmpty();
}

function setupScrambler()
{
	scrambler = new Scrambler(AMOUNT_MOVES);
}

function setupColor(r,g,b)
{
	color = {};
	color.r = r;
	color.g = g;
	color.b = b;
}


function generateNewEnvironment()
{
	canvas = createCanvas(env.width, env.height);
	canvas.position(window.innerWidth * 0.25, window.innerHeight * 0.07);
}

let i_obstacles;
let p_percentAnim;
function setupDom()
{
		// two main elements.
	let mainDiv = Dom.createDiv("row interactiveBlock", document.getElementById("pageContainer"));
	let div = Dom.createDiv("col-md-3", mainDiv);

	
	Dom.createPara("aStarText", "A* : ", div);
	let b_aStar = Dom.createButton("btn btn-primary btn-danger", "Launch A*", div);
	b_aStar.onclick = launchAstar;
	Dom.createPara("","",div);

	Dom.createPara("aStarText", "Scrambler : ", div);
	let b_scrambler = Dom.createButton("btn btn-primary btn-danger", "Launch scramble", div);
	b_scrambler.onclick = launchScramble;
	Dom.createPara("","",div);

	// Elements qui concerne le nombre d'obstacle.
	p_percentAnim = Dom.createPara("aStarText", "Animation Speed : " + tmpPercent, div);
	i_obstacles = Dom.createRange(1, 100, div, "");
	i_obstacles.value = PERCENT;

}
