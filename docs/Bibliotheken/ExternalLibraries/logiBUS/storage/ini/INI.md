# INI

![INI](./INI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **INI** dient dem sicheren Lesen und Schreiben von Konfigurationsdaten in einer `settings.ini`-Datei. Er ermöglicht den Zugriff auf Werte über einen Abschnitts- und Schlüsselnamen und stellt sowohl Initialisierungs- als auch Lese- und Schreiboperationen als getrennte Ereignisse bereit. Durch die Verwendung generischer Datentypen (`ANY`) ist er flexibel einsetzbar.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name   | Typ     | Kommentar                                    |
|--------|---------|----------------------------------------------|
| INIT   | EInit   | Initialisiert den Baustein und öffnet die INI-Datei |
| SET    | Event   | Schreibt den Wert von `VALUE` für den aktuellen Schlüssel   |
| GET    | Event   | Liest den Wert des aktuellen Schlüssels              |

### **Ereignis-Ausgänge**

| Name   | Typ     | Kommentar                                    |
|--------|---------|----------------------------------------------|
| INITO  | EInit   | Bestätigung der Initialisierung             |
| SETO   | Event   | Bestätigung des Schreibvorgangs            |
| GETO   | Event   | Bestätigung des Lesevorgangs               |

### **Daten-Eingänge**

| Name          | Typ    | Kommentar                                    |
|---------------|--------|------------------------------------------------|
| QI            | BOOL   | Event-Input-Qualifier (steuert die Ausführung) |
| SECTION       | STRING | Name des Abschnitts in der INI-Datei          |
| KEY           | STRING | Schlüsselname innerhalb des Abschnitts        |
| VALUE         | ANY    | Wert, der gesetzt werden soll (bei SET)       |
| DEFAULT_VALUE | ANY    | Standardwert, falls Schlüssel nicht existiert (bei GET) |

### **Daten-Ausgänge**

| Name    | Typ    | Kommentar                                    |
|---------|--------|------------------------------------------------|
| QO      | BOOL   | Event-Output-Qualifier (zeigt Erfolg/Misserfolg an) |
| STATUS  | STRING | Statusinformationen (z. B. Fehlertext)        |
| VALUEO  | ANY    | Ausgelesener Wert (bei GET) oder bestätigter gesetzter Wert |

### **Adapter**

Keine Adapter definiert.

## Funktionsweise

Der Baustein arbeitet auf einer Datei `settings.ini`, die eine einfache Schlüssel-Wert-Struktur in Abschnitten (`[Section]`) enthält. Die Nutzung erfolgt in drei Schritten:

1. **INIT** – Mit dem INIT-Ereignis werden die Parameter `SECTION` und `KEY` übergeben. Der Baustein öffnet oder lädt die INI-Datei und bereitet die Lese-/Schreiboperationen vor. Eine erfolgreiche Initialisierung wird durch das INITO-Ereignis signalisiert.

2. **SET** – Nach der Initialisierung kann mit SET ein neuer Wert für den zuvor definierten Schlüssel geschrieben werden. Der übergebene `VALUE` wird in der INI-Datei gespeichert. Der Ausgang `VALUEO` gibt den geschriebenen Wert zurück.

3. **GET** – Mit GET wird der aktuelle Wert des Schlüssels gelesen. Existiert der Schlüssel nicht, wird der über `DEFAULT_VALUE` angegebene Standardwert zurückgegeben. Der gelesene Wert erscheint am Ausgang `VALUEO`.

Die Ausführung jedes Ereignisses wird durch den jeweiligen Ausgang (INITO, SETO, GETO) quittiert. Dabei zeigt `QO` an, ob die Operation erfolgreich war, und `STATUS` liefert eine textuelle Rückmeldung.

## Technische Besonderheiten

- **Generische Datentypen** – `VALUE` und `DEFAULT_VALUE` sind als `ANY` deklariert. Der Baustein kann daher mit verschiedenen Datentypen (z. B. BOOL, INT, REAL, STRING) arbeiten, sofern die Laufzeitumgebung diese unterstützt.
- **Event-basierte Steuerung** – Alle Aktionen werden über Ereignisse ausgelöst. Der Baustein ist somit vollständig in ein ereignisgesteuertes System (z. B. IEC 61499) integrierbar.
- **Fehlerbehandlung** – Der Ausgangsqualifier `QO` und der `STATUS`-String ermöglichen eine einfache Fehlerdiagnose (z. B. bei nicht vorhandener Datei oder ungültigem Abschnitt).

## Zustandsübersicht

Der Funktionsblock durchläuft folgende Hauptzustände:

- **Idle** – Warten auf INIT.
- **Initialized** – Nach erfolgreichem INIT; bereit für SET oder GET.
- **Error** – Bei fehlgeschlagener Initialisierung oder Operation; nur ein erneutes INIT kann den Zustand verlassen.

Die Zustandsübergänge werden durch die Ereignisse INIT, SET und GET sowie die entsprechenden Bestätigungsausgänge gesteuert.

## Anwendungsszenarien

- **Maschinenkonfiguration** – Speichern und Abrufen von Parametern wie Geschwindigkeit, Temperaturgrenzen oder Betriebsmodi in einer zentralen INI-Datei.
- **Anlageninitialisierung** – Einmaliges Laden von Einstellungen beim Start der Steuerung über das INIT-Ereignis.
- **Online-Parametrierung** – Dynamisches Ändern von Werten während des Betriebs mittels SET und sofortiges Auslesen mit GET.

## Vergleich mit ähnlichen Bausteinen

| Baustein   | Datenquelle      | Typunterstützung      | Ereignisschnittstelle |
|------------|------------------|-----------------------|-----------------------|
| INI        | settings.ini     | ANY (generisch)       | INIT, SET, GET        |
| FILE_READ  | Textdatei        | STRING                | REQ, CNF              |
| PARAM_DB   | Datenbank        | typspezifisch         | komplexer             |

Der INI-Baustein punktet durch seine Einfachheit und die direkte Anbindung an INI-Dateien, ohne zusätzliche Treiber oder Datenbanken. Andere Bausteine bieten entweder mehr Flexibilität (Datenbank) oder sind auf reine Text-Ein-/Ausgabe beschränkt.

## Fazit

Der INI-Funktionsblock stellt eine kompakte und zuverlässige Lösung für die dauerhafte Speicherung von Konfigurationsdaten in IEC-61499-Systemen dar. Seine generische Datentypdefinition und die klare Ereignissteuerung machen ihn vielseitig einsetzbar. Durch die integrierte Fehlerbehandlung eignet er sich sowohl für Entwicklungs- als auch für Produktionsumgebungen.