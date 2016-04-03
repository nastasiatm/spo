
#!/usr/bin/ksh
IFS=
trap "" 2
log=$HOME/lab2-1_err
filename=$1
if [ -a $filename ]
then
else
    echo "$filename: No such file" 1>&2
fi;;




while true
    echo "Input file nameпроверка на ссылки ключ -h "
    echo "2. Сменить текущий каталог"
    echo "3. Создать файл"
    echo "4. Прoедоставить всем право на запись в файл"
    echo "5. Удалить файл"
    echo "6. Выйти из программы"
    read doing
    do
    case $doing in
        1)
                pwd 2>>$log || echo "Display name of the current directory error!";;
        2)
            echo "Input adress and press Enter."
            read address
            cd "$PWD" "$address" 2>>$log || echo "Transition error!" 1>&2;;
        3)
            echo "Input name of new file and press Enter."
            read nfile
            touch -- "$nfile" 2>>$log || echo "Creation error!" 1>&2 ;;
        4)
            echo "Input file name and press Enter."
            read rfile
            if [ -f $rfile ]
            then
                chmod -- a+w "$rfile" 2>>$log || echo "Rights assignment error!" 1>&2
            else
                echo "File does not exist." 1>&2
            fi;;

        5)
            echo "Input file name and press Enter."
            read dfile
            if [ -a $dfile ]
            then
                echo "rm: remove $dfile (yes/no)?"
                read ans
                if [ "$ans" == "yes" ]
                then
                    rm -- "$dfile" 2>>$log || echo "Remove error!" 1>&2
                elif [ "$ans" == "no" ]
                then
                    echo "File will not be removed."
                else
                    echo "Input error!"
                fi
            else
                echo "$dfile: No such file or directory" 1>&2
            fi;;
        6)
            exit 0 ;;
        *)
            echo "Error! Input command number and press Enter."
            echo "$(date)     $USER     Invalid command number" >> $log;;
        esac
done
getent group > gr.txt; grep 'p3202' gr.txt

























