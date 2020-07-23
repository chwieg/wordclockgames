<script>
 let myTodo = getTodo();

 async function getTodo() {
   const response = await fetch("https://jsonplaceholder.typicode.com/todos/1");
   const todo = await response.json();

   if (response.ok) {
     return todo;
   } else {
     throw new Error(todo);
   }
 }

</script>

{#await myTodo}
    <p>...waiting</p>
{:then todo_1}
    <p>{todo_1.title}</p>
{:catch error}
    <p style="color: red">{error.message}</p>
{/await}
