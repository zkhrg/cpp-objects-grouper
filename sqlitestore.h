#ifndef SQLITESTORE_H
#define SQLITESTORE_H
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QtSql>
#include <iostream>
#include <string>

#include "store.h"

class SqliteStore : public Store {
 public:
  SqliteStore();
  bool InitStore(std::string &dbPath) override;
  void InsertData(const std::vector<Object> &v) override;
  std::vector<ViewObject> getObjects(eGrouping grouping, int pageSize,
                                     int pageNumber) override;
};

const QString groupByTypeSizeQuery = R"(
        WITH GroupedData AS (
            SELECT 
                group_type, 
                COUNT(*) AS type_count
            FROM 
                objects
            GROUP BY 
                group_type
        ),
        CategorizedData AS (
            SELECT 
                group_type,
                CASE 
                    WHEN type_count > :group_size THEN group_type
                    ELSE 'Разное'
                END AS group_name
            FROM 
                GroupedData
        ),
        FinalData AS (
            SELECT 
                o.id,
                o.name,
                o.x AS xCoord,
                o.y AS yCoord,
                o.group_type AS gType,
                o.time AS timeStamp,
                cd.group_name
            FROM 
                objects o
            JOIN 
                CategorizedData cd
            ON 
                o.group_type = cd.group_type
        ),
        OrderedData AS (
            SELECT
                id,
                name,
                xCoord,
                yCoord,
                gType,
                timeStamp,
                group_name
            FROM
                FinalData
            ORDER BY
                CASE 
                    WHEN group_name != 'Разное' THEN 1
                    ELSE 2
                END,
                group_name,
                name
        )
        SELECT 
            name,
            xCoord,
            yCoord,
            gType,
            timeStamp,
            group_name
        FROM 
            OrderedData
  LIMIT :page_size OFFSET :offset;
    )";
const QString groupByName = R"(WITH GroupedData AS (
    SELECT 
        CASE
            WHEN substr(name, 1, 1) BETWEEN 'A' AND 'Z' THEN upper(substr(name, 1, 1))
            WHEN substr(name, 1, 1) BETWEEN 'a' AND 'z' THEN upper(substr(name, 1, 1))
            ELSE '#'
        END AS group_char,
        COUNT(*) AS type_count
    FROM 
        objects
    GROUP BY 
        group_char
),
CategorizedData AS (
    SELECT 
        group_char,
        CASE 
            WHEN type_count > 1 THEN group_char
            ELSE '#'
        END AS group_name
    FROM 
        GroupedData
),
FinalData AS (
    SELECT 
        o.id,
        o.name,
        o.x AS xCoord,
        o.y AS yCoord,
        o.group_type AS gType,
        o.time AS timeStamp,
        cd.group_name
    FROM 
        objects o
    JOIN 
        CategorizedData cd
    ON 
        CASE
            WHEN substr(o.name, 1, 1) BETWEEN 'A' AND 'Z' THEN upper(substr(o.name, 1, 1))
            WHEN substr(o.name, 1, 1) BETWEEN 'a' AND 'z' THEN upper(substr(o.name, 1, 1))
            ELSE '#'
        END = cd.group_char
),
OrderedData AS (
    SELECT
        id,
        name,
        xCoord,
        yCoord,
        gType,
        timeStamp,
        group_name
    FROM
        FinalData
    ORDER BY
        CASE 
            WHEN group_name != '#' THEN 1
            ELSE 2
        END,
        group_name,
        name
)
SELECT 
    name,
    xCoord,
    yCoord,
    gType,
    timeStamp,
    group_name
FROM
    OrderedData
LIMIT :page_size OFFSET :offset;
)";

const QString groupByDate = R"(WITH DateCategorizedData AS (
    SELECT
        id,
        name,
        x AS xCoord,
        y AS yCoord,
        group_type AS gType,
        time AS timeStamp,
        CASE
            WHEN datetime(time, 'unixepoch', 'localtime') BETWEEN datetime('now', 'start of day') AND datetime('now', '+1 day', '-1 second') THEN 'Сегодня'
            WHEN datetime(time, 'unixepoch', 'localtime') BETWEEN datetime('now', '+1 day', 'start of day') AND datetime('now', '+2 day', '-1 second') THEN 'Завтра'
            WHEN strftime('%Y', datetime(time, 'unixepoch', 'localtime')) = strftime('%Y', 'now') THEN 'В этом году'
            WHEN strftime('%Y', datetime(time, 'unixepoch', 'localtime')) >= strftime('%Y', 'now', '-100 year') THEN 'В этом веке'
            ELSE 'Старее'
        END AS group_name
    FROM 
        objects
),
OrderedData AS (
    SELECT
        id,
        name,
        xCoord,
        yCoord,
        gType,
        timeStamp,
        group_name
    FROM
        DateCategorizedData
    ORDER BY
        CASE
            WHEN group_name = 'Сегодня' THEN 1
            WHEN group_name = 'Завтра' THEN 2
            WHEN group_name = 'В этом году' THEN 3
            WHEN group_name = 'В этом веке' THEN 4
            ELSE 5
        END,
        timeStamp,
        name
)
SELECT 
    name,
    xCoord,
    yCoord,
    gType,
    timeStamp,
    group_name
FROM 
    OrderedData
LIMIT :page_size OFFSET :offset;
)";

const QString groupByDistance = R"(WITH DistanceCategorizedData AS (
    SELECT
        id,
        name,
        x AS xCoord,
        y AS yCoord,
        group_type AS gType,
        time AS timeStamp,
        -- Рассчитываем расстояние от точки (0,0)
        sqrt(x * x + y * y) AS distance,
        CASE
            WHEN sqrt(x * x + y * y) <= 500 THEN 'до 500'
            WHEN sqrt(x * x + y * y) <= 1000 THEN 'до 1000'
            WHEN sqrt(x * x + y * y) <= 5000 THEN 'до 5000'
            ELSE 'далеко'
        END AS group_name
    FROM 
        objects
),
OrderedData AS (
    SELECT
        id,
        name,
        xCoord,
        yCoord,
        gType,
        timeStamp,
        group_name,
        distance
    FROM
        DistanceCategorizedData
    ORDER BY
        CASE
            WHEN group_name = 'до 500' THEN 1
            WHEN group_name = 'до 1000' THEN 2
            WHEN group_name = 'до 5000' THEN 3
            ELSE 4
        END,
        distance, -- Сортируем по расстоянию внутри каждой категории
        name
)
SELECT 
    name,
    xCoord,
    yCoord,
    gType,
    timeStamp,
    group_name
FROM 
    OrderedData
LIMIT :page_size OFFSET :offset;
)";

#endif  // SQLITESTORE_H
