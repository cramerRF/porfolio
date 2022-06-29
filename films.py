import mysql.connector
from mysql.connector import Error

def dfs_movies_edge_person_cast(queue, id_2, cursor):
    bar = ["\\", "|", "/", "-"]
    i = 0
    explored = []
    explored_persons = []
    n = 1
    while (1):
        new_q = []
        while (len(queue)):
            print(bar[i], end="\r")
            i += 1
            i %= 4
            next_id = queue.pop(0)
            explored.append(next_id)
            query = "SELECT person_id FROM movie_cast WHERE movie_id LIKE '" + str(next_id) + "';"
            cursor.execute(query)
            result = cursor.fetchall()
            s_r = []
            for r in result:
                if r[0] not in explored_persons:
                    s_r.append(r[0])
                    explored_persons.append(r[0])
            if id_2 in s_r:
                print("explored films: " + str(len(explored)))
                print("explored persons: " + str(len(explored_persons)))
                return n
            query = "SELECT movie_id FROM movie_cast WHERE person_id in (SELECT person_id FROM movie_cast WHERE movie_id LIKE '" + str(next_id) + "');"
            cursor.execute(query)
            result = cursor.fetchall()
            for r in result:
                if r[0] not in explored:
                    new_q.append(r[0])
        queue = new_q
        n += 1

def get_films_btw_id(id_1, id_2, cursor):
    queue = []
    query = "SELECT movie_id FROM movie_cast WHERE person_id LIKE '" + str(id_1) + "';"
    cursor.execute(query)
    result = cursor.fetchall()
    for r in result:
        queue.append(r[0])
    sol = []
    return dfs_movies_edge_person_cast(queue, id_2, cursor)
    
def get_films_n(t):
    try:
        connection = mysql.connector.connect(
            host='34.77.53.130',
            database='movies',
            user='root',
            password='1234')
        if connection.is_connected():
            db_info = connection.get_server_info()
            cursor = connection.cursor()
            if t:
                query = "SELECT person_name FROM person;"
                cursor.execute(query)
                result = cursor.fetchall()
                for p in result:
                    print(p[0])
            n_1 = input("Introduce la primera persona: ")
            n_2 = input("Introduce la segunda persona: ")
            query = "SELECT person_id FROM person WHERE person_name LIKE '" + n_1 + "';"
            cursor.execute(query)
            result = cursor.fetchall()
            if (len(result) != 1):
                return ("Bad name_1")
            id_1 = result[0][0]
            query = "SELECT person_id FROM person WHERE person_name LIKE '" + n_2 + "';"
            cursor.execute(query)
            result = cursor.fetchall()
            if (len(result) != 1):
                return ("Bad name_2")
            id_2 = result[0][0]
            sol = str(id_1) + " " + str(id_2)
            sol = get_films_btw_id(id_1, id_2, cursor)
            connection.close()
            print("Entre " + n_1 + " y " + n_2  + "hay " + str(sol) + " peliculas de distancia")
            return (sol)
    except Error as e:
        print("Error", e)

get_films_n(False)
