window.onload=function(){
    const downloadToFile = (content, filename, contentType) => {
        const a = document.createElement('a');
        const file = new Blob([content], {type: contentType});
        
        a.href= URL.createObjectURL(file);
        a.download = filename;
        a.click();
        
        URL.revokeObjectURL(a.href);
    };
    
    document.getElementById('btnSave').addEventListener('click', () => {
        var input = "";
        for (var i = 0; i < 3; i++)
        {
            for (var j = 0; j < 3; j++)
            {
                input += document.getElementById(EntryStr(i + 1, j + 1)).value;
            }
            input += "\n";
        }

        downloadToFile(input, 'my-new-file.txt', 'text/plain');
    });
}

function EntryStr(row,col)
{
    let rowStr = row.toString();
    let colStr = col.toString();
    return "a" + rowStr + colStr;
}



