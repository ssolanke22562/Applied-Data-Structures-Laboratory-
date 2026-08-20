<h2>Task Scheduling / Minimum Work Per Day (Capacity To Ship Packages Within D Days)</h2>
<h3>Binary Search on Answer</h3>
<hr>
<p>Given an array of <code>n</code> task workloads and <code>d</code> days, find the minimum maximum work limit per day such that all tasks can be completed within <code>d</code> days.</p>

<p>&nbsp;</p>
<p><strong>Example:</strong></p>
<pre>
<strong>Input:</strong>
Number of tasks: 5
Task workloads: 1 2 3 4 5
Number of days: 3

<strong>Output:</strong>
Minimum work per day = 6
</pre>

<p>&nbsp;</p>
<p><strong>Algorithm:</strong></p>
<ul>
	<li>Use Binary Search on the answer range: <code>[max(task), sum(task)]</code>.</li>
	<li>For a candidate limit <code>mid</code>, check if all tasks can be scheduled in <code>&lt;= d</code> days.</li>
	<li>Adjust search space based on feasibility.</li>
</ul>
