# GET_DATE_AND_TIME


![GET_DATE_AND_TIME](./GET_DATE_AND_TIME.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **GET_DATE_AND_TIME** dient dazu, einen Wert vom Typ `DATE_AND_TIME` aus einer als InOut deklarierten Variable auszulesen und als gepufferten (gebufferten) Ausgang bereitzustellen. Bei jeder Anforderung wird der aktuelle Wert der Quelle (InOut-Variable) auf den Ausgang kopiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Mit | Beschreibung |
|----------|-----|--------------|
| REQ      | IN  | Normale Ausführungsanforderung; löst das Auslesen der Quelldaten aus. |

### **Ereignis-Ausgänge**

| Ereignis | Mit              | Beschreibung |
|----------|------------------|--------------|
| CNF      | OUT, IN          | Bestätigung der Ausführung; signalisiert, dass der Ausgang aktualisiert wurde. |

### **Daten-Eingänge**

| Name | Typ           | Beschreibung |
|------|---------------|--------------|
| IN   | DATE_AND_TIME | InOut-Variable als Quelle der Daten. Sie wird gelesen, aber nicht verändert. |

### **Daten-Ausgänge**

| Name | Typ           | Beschreibung |
|------|---------------|--------------|
| OUT  | DATE_AND_TIME | Gepufferter Ausgangswert, der bei jedem REQ aus der InOut-Quelle übernommen wird. |

### **Adapter**

Keine.

## Funktionsweise

Der Baustein besitzt einen einfachen internen Zustand **REQ**. Beim Eintreten dieses Zustands (ausgelöst durch das Ereignis `REQ`) wird folgender Algorithmus ausgeführt:

```
OUT := IN;
```

Anschließend wird das Ereignis `CNF` gesendet. Der Wert der InOut-Variable `IN` wird dabei nicht verändert; er wird lediglich ausgelesen und in den Ausgang `OUT` kopiert. Somit arbeitet der Baustein als **Puffer** für einen beliebigen `DATE_AND_TIME`-Wert.

## Technische Besonderheiten

- Die Verwendung einer **InOut-Variable** (`IN`) erlaubt den direkten Zugriff auf eine externe Variable, ohne dass diese als separater Ein- oder Ausgang deklariert werden muss. Der Baustein greift lesend darauf zu.
- Der Ausgang `OUT` speichert den zum Zeitpunkt des `REQ` vorliegenden Wert. Ändert sich die Quelle zwischen zwei `REQ`-Aufrufen, wird der neue Wert erst mit dem nächsten `REQ` übernommen (gepufferte Bereitstellung).
- Es handelt sich um einen **einfachen Funktionsblock** (SimpleFB) ohne komplexe Zustandsautomatik – nur ein einziger Ausführungszustand.

## Zustandsübersicht

| Zustand | Aktion | Ausgabeereignis |
|---------|--------|-----------------|
| REQ     | `OUT := IN;` | CNF |

Es gibt keinen Initialzustand oder sonstige Zustände; der Baustein wartet auf das Ereignis `REQ` und führt sofort den Algorithmus aus.

## Anwendungsszenarien

- **Zeitstempel-Erfassung**: Abrufen des aktuellen Zeitpunkts aus einer Systemuhr, die als InOut-Variable bereitsteht, zu einem definierten Steuerungszeitpunkt.
- **Pufferung von Datums-/Zeitwerten**: Zwischenspeichern eines momentanen Datums-/Zeitwerts für spätere Verarbeitungsschritte.
- **Synchronisation**: Übernahme eines gemeinsamen Zeitwerts aus einer zentralen Quelle in verschiedene Funktionsbausteine.

## Vergleich mit ähnlichen Bausteinen

- **GET_DATE_AND_TIME** im Gegensatz zu Bausteinen wie `E_GET_TIME` (Echtzeit-Uhr-Abfrage) oder `TIME_GET` (aktuelle Systemzeit): Dieser Baustein arbeitet nicht mit einer fest eingebauten Uhr, sondern liest aus einer beliebigen InOut-Variable. Dadurch ist er flexibler einsetzbar, z.B. für den Zugriff auf applikationsspezifische Zeitwerte.
- Im Vergleich zu einem einfachen Zuweisungsbaustein (z.B. `MOVE` mit `DATE_AND_TIME`) bietet er eine ereignisgesteuerte, explizite Anforderung und explizite Bestätigung (`REQ`/`CNF`), was für zeitkritische Steuerungen vorteilhaft ist.

## Fazit

**GET_DATE_AND_TIME** ist ein schlanker, klar strukturierter Funktionsblock, der das Auslesen und Puffern eines `DATE_AND_TIME`-Werts aus einer InOut-Variable ermöglicht. Seine einfache Handhabung und die explizite Ereignissteuerung machen ihn zu einem nützlichen Werkzeug für die zuverlässige Übernahme von Zeitdaten in Automatisierungsanwendungen.