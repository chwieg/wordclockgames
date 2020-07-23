<script>
	
	let arr = [0,1,2,3];
	let foo = 'baz'
	let bar = 'qux'
	let url = "http://localhost:8080/wordclock/connectfour"
	let game = getData();

 	async function getData() { 
        const resp = await fetch(url); 
	 	const json = await resp.json(); 
        if (response.ok) { 
            return json;
        } else { 
            throw new Error(json); 
        } 
    }
		
	async function putData(col=0) {
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
		game = json;

	}

</script>

<style>
</style>


{#await game then result}
<div>
{#each arr as el, i}
	<button class="button" on:click={() => putData(i)}>
		Clicked
	</button>
{/each}
</div>


<input bind:value={foo} />
<input bind:value={bar} />
<button type="button" on:click={() => putData(100)}>
	Post it.
</button>

<p> Result: </p>
<p>State:         {result.State}</p>
<p>Act. Player:   {result.ActivePlayer}</p>
<p>Allowed Moves: {result.AllowedMoves}</p>
<p>Board:         {result.Board}</p>

{/await}
