<h1>K-- (Programming Language)</h1>

<h2>Project Overview</h2>
<p><code>K--</code> is a lightweight and flexible interpreted programming language. It features its own unique syntax and supports the definition of variables and functions. Additionally, it includes a variety of standard functions such as <code>print</code>, <code>println</code>, and <code>input</code>, making it easy to start coding right away.</p>

<h2>Features</h2>
<ul>
    <li><strong>Flexibility:</strong> K-- is extensible and modifiable, allowing you to tailor the language to suit your project's specific needs.</li>
    <li><strong>Standard Functions:</strong> Includes ready-to-use standard functions for immediate development.</li>
    <li><strong>Lightweight:</strong> With its minimalist design and low memory consumption, K-- is a fast and efficient interpreter.</li>
    <li><strong>Custom Syntax:</strong> Offers a unique syntax that is simple yet powerful.</li>
</ul>

<h2>Getting Started</h2>
<p>To start using K--, follow these steps:</p>
<ol>
    <li>Compile the source code:</li>
    <pre><code>gcc -o kaan k_interpreter.c</code></pre>
    <li>Create your K-- script using a text editor and save it with a <code>.k</code> extension. For example, <code>example.k</code>.</li>
    <li>Run the script using the following command:</li>
    <pre><code>./kaan example.k</code></pre>
</ol>

<h2>Example Usage</h2>

<h3>Variable Definition</h3>
<p>Variables can be defined with types such as <code>string</code>, <code>int</code>, and <code>bool</code>:</p>
<pre><code>// var type variable_name = variable_value ;

var string name = "kaan";    // defining a string variable
var string surname;          // declaring a string variable
var int age = 19;            // defining an integer variable
var bool isHungry = true;    // defining a boolean variable
</code></pre>

<h3>Variable Assignment</h3>
<p>Assign values to variables as follows:</p>
<pre><code>// variable_name = variable_value ;

var string name = "hello world";
name = "kaan";
</code></pre>

<h3>Function Calls</h3>
<p>Call functions using the following syntax:</p>
<pre><code>// function_name : param1 , param2 ;

println: "hello world";
print: "hello world";
</code></pre>

<h3>Function Definition</h3>
<p>Functions are defined using this structure:</p>
<pre><code>// func function_name ( parameter1 , parameter2 )
// {
// }

func example(x)
{
  println: x;
}
</code></pre>

<h3>Conditional Statements</h3>
<p>Use if/else statements to control the flow of your program:</p>
<pre><code>// if ( condition )
// {
// }
// else
// {
// }

var int x = 10;
if (x == 10)
{
  println: "x is 10";
}
else
{
  println: "x is not 10";
}
</code></pre>

<h2>Advanced Features</h2>
<p>K-- also supports loops, user-defined types, and more advanced programming constructs:</p>

<h3>Loops</h3>
<p>Use loops to repeat code execution:</p>
<pre><code>// while ( condition )
// {
// }

var int i = 0;
while (i < 10)
{
  println: i;
  i = i + 1;
}
</code></pre>

<h3>User-Defined Types</h3>
<p>Create and use your own types:</p>
<pre><code>// type typeName
// {
//     type propertyName;
// }

type Person
{
  string name;
  int age;
}

var Person p;
p.name = "John";
p.age = 30;
</code></pre>

<h2>Conclusion</h2>
<p>K-- is a versatile and efficient programming language suitable for a wide range of projects. Its flexibility and lightweight nature make it an excellent choice for developers looking for a customizable and quick-to-implement interpreted language.</p>
