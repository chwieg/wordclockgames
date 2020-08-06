<script>
	
	let url =        "http://192.168.0.242:8080"
	//let url =        "http://localhost:8080"
	let urlCon4 =    url+"/con4"
	let urlNewGame = urlCon4+"/newgame"
	let urlRemote =  url+"/remote"

	let game = getData()
	let buttonLabels = "EIVIERT"
	// variables for Binding buttons disabled 
	let i = 0
	let arr = []
	let remoteButtons = [
		["TIME", "0xFFA05F"],
		["REGION", "0xFF20DF"],
		["SECONDS", "0xFF609F"],
		["ON_OFF", "0xFFE01F"],

		["RED", "0xFF906F"],
		["GREEN", "0xFF10EF"],
		["DARKBLUE", "0xFF50AF"],
		["PINK", "0xFFD02F"],
		["WHITE", "0xFFB04F"],
		["BRIGHTBLUE", "0xFF30CF"],
		["YELLOW", "0xFF708F"],
		["RGB", "0xFFF00F"],

		["NORMAL", "0xFFA857"],
		["FADE", "0xFF28D7"],
		["MATRIX", "0xFF6897"],
		["SLIDE", "0xFFE817"],

		["STD_PLUS", "0xFF9867"],
		["STD_MINUS", "0xFF8877"],
		["MIN_PLUS", "0xFF18E7"],
		["MIN_MINUS", "0xFF08F7"],

		["BRIGHTER", "0xFF58A7"],
		["DARKER", "0xFF48B7"],

		["LDR", "0xFFD827"],
		["MODE", "0xFFC837"],
	]


	async function getData() { 
		console.log("fetching data");
		const resp = await fetch(urlCon4); 
		const json = await resp.json(); 
        if (resp.ok) { 
			console.log("response: "+resp.body);
            return json;
        } else { 
			console.log("Error: "+resp);
            //throw new Error(json); 
            throw new Error(resp); 
        } 
    }

 	async function newGame() { 
		console.log("fetching data");
		const resp = await fetch(urlNewGame); 
		const json = await resp.json(); 
        if (resp.ok) { 
			console.log("response: "+resp.body);
            game = json;
        } else { 
			console.log("Error: "+resp);
            //throw new Error(json); 
            throw new Error(resp); 
        } 
    }
	
	async function putData(col) {
		const payload = JSON.stringify({
      			column: col
    		});
		console.log("payload: "+payload);
		const resp = await fetch(urlCon4, {
		    method: 'PUT',
    		body: JSON.stringify({
      			column: col
    		}),
    		headers: {
      			"Content-type": "application/json; charset=UTF-8"
    		}
		})
		const json = await resp.json()
     	if (resp.ok) { 
			console.log("response: "+resp.body);
       //     return json;
			game = json;
			arr = !game.AllowedMoves
        } else { 
			console.log("Error: "+resp);
            //throw new Error(json); 
            throw new Error(resp); 
        } 
	}
	
	function isAllowed(i, arr) {
		return !arr[i]
	}

	async function putRemoteCommand(code) {
		const resp = await fetch(urlRemote, {
		    method: 'PUT',
    		body: JSON.stringify({
      			buttonCode: code
    		}),
    		headers: {
      			"Content-type": "application/json; charset=UTF-8"
    		}
		})
	}
	
</script>

<style>
.grid-container-remote {
  display: grid;
  grid-gap: 1em;
  grid-template-columns: repeat(4, auto);
}
.grid-item-remote {
	margin: 0;
}
.grid-container-move {
  display: grid;
  grid-gap: 1em; 
  grid-template-columns: repeat(7, auto);
}
</style>


{#await game}
	<p>Loading...</p>
{:then result}
<div style="width:35em">
	<h1>Fernbedienung</h1>
	<div class="grid-container-remote">
	{#each remoteButtons as button}
		<button class="grid-item-remote" on:click={() => putRemoteCommand(button[1])}>
			{button[0]}
		</button>
	{/each}
	</div>
	<h1>4 gewinnt</h1>
	<div class="grid-container-move">
	{#each result.AllowedMoves as el, i}
		<button class="button" disabled='{isAllowed(i,result.AllowedMoves)}' on:click={() => {putData(i)
			console.log("Index: "+i)}}>
			{buttonLabels.charAt(i)}
		</button>
	{/each}
	</div>
	<div>
	<button class="button" on:click={() => newGame()}>
		neues Spiel	
	</button>
	</div>

	<p>Result: </p>
	<p>State:         {result.State}</p>
	<p>Act. Player:   {result.ActivePlayer}</p>
	<p>Allowed Moves: {result.AllowedMoves}</p>
	<p>Board:</p>
	{#each result.Board as row}
		<p>{row}</p>
	{/each}
</div>
{:catch error}
	<p>Error. Promise not kept :(</p>
{/await}

