<script>
	
	let url =        "http://localhost:8080/con4"
	let urlNewGame = url+"/newgame"
	let game = getData()
	let i = 0
	let arr = []

	async function getData() { 
		console.log("fetching data");
		const resp = await fetch(url); 
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
		const resp = await fetch(url, {
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

</script>

<style>
</style>


{#await game}
	<p>Loading...</p>
{:then result}
	<div>
	{#each result.AllowedMoves as el, i}
		<button class="button" disabled='{isAllowed(i,result.AllowedMoves)}' on:click={() => {putData(i)
			console.log("Index: "+i)}}>
			Spalte {i}
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
{:catch error}
	<p>Error...</p>
{/await}

