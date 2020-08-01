<script>
	
	let arr = [0,1,2,3];
	let foo = 'baz'
	let bar = 'qux'
	let url = "http://localhost:8080/wordclock/connectfour"
	//let url = "http://ip.jsontest.com/"
	let game = getData();

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
        } else { 
			console.log("Error: "+resp);
            //throw new Error(json); 
            throw new Error(resp); 
        } 
	}

</script>

<style>
</style>
{#await game}
<p>Loading...</p>

{:then result}
{#each result.AllowedMoves as el, i}
	<button class="button" on:click={() => {putData(i)
console.log("Index: "+i)}}>
		Clicked
	</button>
{/each}
	<button class="button" on:click={() => getData()}>
		Clicked
	</button>

<!--<p>ip:         {result.ip}</p> -->
<p> Result: </p>
<p>State:         {result.State}</p>
<p>Act. Player:   {result.ActivePlayer}</p>
<p>Allowed Moves: {result.AllowedMoves}</p>
<p>Board:         {result.Board}</p>

{#each result.Board as row}

<p>{row}</p>

{/each}

{:catch error}
<p>Error...</p>
{/await}
<!--
{#await game}
<p>Loading...</p>

{:then result}
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
{:catch error}
<p>Error...</p>
{/await}
-->
