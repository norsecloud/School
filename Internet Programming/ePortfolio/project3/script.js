function performStatistics()
{
    //turn string into array
    var array = document.getElementById("input").value;
    array = array.split(/[ ,]+/).map(Number);
    //check is correct length
    if (array.length<5 || array.length>20)
    {
        alert("Must enter more than 5 numbers, but less than 20.");
        return false
    }
    //check if numbers in array are numbers and between 0-100
    for(let i=0; i<array.length; i++)
    {
        if (isNaN(array[i]))
        {
            alert("Please Enter only Numbers.");
            return false;
        }
        if (array[i]<0 || array[i]>100)
        {
            alert("Numbers must be in between 0 to 100.");
            return false
        }
    }
    //sort array
    array.sort(function(a, b){return a-b});
    //pass array to functions
    document.getElementById("Sum").value = calcSum(array);
    document.getElementById("Mean").value = calcMean(array);
    document.getElementById("Median").value = calcMedian(array);
    document.getElementById("Min").value = findMin(array);
    document.getElementById("Max").value = findMax(array);
    document.getElementById("Variance").value = calcVariance(array);
    document.getElementById("std").value = calcStdDev(array).toFixed(2);
    document.getElementById("Mode").value = calcMode(array);

    return false;
}
function calcMean(array)
{
    return (calcSum(array)/array.length).toFixed(2);
}
function calcMedian(array)
{
    return array[Math.floor(array.length/2)].toFixed(2);
}
function calcMode(array)
{
    var dict = {};
    var mode = array[0];
    var amount;
    var string = "";

    for (let i = 0; i < array.length; i++)
    {
        if(dict[array[i]] !== undefined)
        {//if in dict then +1 to key
            dict[array[i]]++;
        }
        else
        {//if not in dict add and set to 1
            dict[array[i]] = 1;
        }
        if (dict[array[i]] > dict[mode])
        {//if number is bigger than cur mode number then replace mode
            mode = array[i];
        }
    }//end for loop
    //find if other values have same amount of numbers
    amount = dict[mode]
    for (let x in dict)
    {//this is for adding more modes
        if (dict[x] === amount)
        {
            string += x + " ";
        }
    }
    return string;
}
function calcStdDev(array)
{
    return Math.sqrt(calcVariance(array))
}
function calcSum(array)
{
    var total = 0;
    for(let i=0; i<array.length; i++)
    {
        total += (array[i]);
    }
    return total.toFixed(2);
}
function calcVariance(array)
{
    var mean = calcMean(array)
    var dif = []
    for(let i=0; i<array.length; i++)
    {
        dif.push(Math.pow((array[i] - mean), 2));
    }
    return calcMean(dif)
}
function findMax(array)
{
    return array[array.length-1].toFixed(2)
}
function findMin(array)
{
    return array[0].toFixed(2)
}