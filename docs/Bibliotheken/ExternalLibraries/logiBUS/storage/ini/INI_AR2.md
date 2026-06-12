# INI_AR2


![INI_AR2](./INI_AR2.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock INI_AR2 dient zum Auslesen und Schreiben von REAL-Werten aus bzw. in eine settings.ini-Datei über einen Sektions- und Schlüsselnamen. Er kapselt einen INI-Funktionsblock und stellt eine bidirektionale AR2-Adapter-Schnittstelle bereit. Beim Initialisierungsereignis wird der Wert für den angegebenen Sektions- und Schlüsselnamen gelesen und über den Adapter ausgegeben. Gleichzeitig können über den Adapter neue Werte empfangen und in die Datei zurückgeschrieben werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT** (EInit): Service-Initialisierung. Löst das Laden des Wertes aus der settings.ini aus und initialisiert den Baustein.

### **Ereignis-Ausgänge**
- **INITO** (EInit): Bestätigung der Initialisierung. Wird nach erfolgreicher Verarbeitung des INIT-Ereignisses gesendet.

### **Daten-Eingänge**
- **QI** (BOOL): Eingangsqualifizierer. Steuert die Ausführung (z.B. Aktivierung/Deaktivierung).
- **SECTION** (STRING): Sektionsname in der settings.ini (z.B. "[MySection]").
- **KEY** (STRING): Schlüsselname in der Sektion (z.B. "MyKey").
- **DEFAULT_VALUE** (REAL): Standardwert, der zurückgegeben wird, falls der Schlüssel in der Datei nicht vorhanden ist.

### **Daten-Ausgänge**
- **QO** (BOOL): Ausgangsqualifizierer. Gibt den Status der Verarbeitung an.
- **STATUS** (STRING): Dienststatusmeldung (z.B. Fehlertext oder "OK").

### **Adapter**
- **VAL** (AR2): Bidirektionaler Adapter vom Typ `adapter::types::bidirectional::AR2`. Über diesen Adapter werden die gelesenen Werte bereitgestellt (Ausgang) und neue Werte empfangen (Eingang) zum Zurückschreiben in die INI-Datei. Der Adapter hat die Ereignisse EO1 (Ausgang) und EI1 (Eingang) sowie Daten DO1 (Ausgang) und DI1 (Eingang).

## Funktionsweise
Der FB INI_AR2 ist ein zusammengesetzter (Composite) Baustein, der intern einen INI-Funktionsblock (`eclipse4diac::storage::INI`) verwendet. Der Ablauf ist wie folgt:

1. **Initialisierung**: Beim Eintreffen des INIT-Ereignisses werden die Parameter QI, SECTION, KEY, DEFAULT_VALUE an den internen INI-Block übergeben.
2. **Lesen**: Der INI-Block führt nach INIT automatisch einen GET-Vorgang aus (gesteuert durch die Eventverbindung von INI.INITO zu INI.GET). Er liest den Wert aus der settings.ini für die angegebene Sektion und den Schlüssel. Falls kein Eintrag vorhanden ist, wird der DEFAULT_VALUE verwendet.
3. **Ausgabe über Adapter**: Der gelesene Wert wird über die Datenverbindung INI.VALUEO -> VAL.DI1 und das Ereignis INI.GETO -> VAL.EI1 an den Adapter-Ausgang weitergegeben.
4. **Schreiben über Adapter**: Wenn über den Adapter ein neuer Wert an VAL.DO1 ankommt (ausgelöst durch VAL.EO1), wird das Ereignis VAL.EO1 -> INI.SET geleitet. Der INI-Block schreibt dann den neuen Wert zurück in die Datei. Nach dem Schreiben wird INI.SETO -> VAL.EI1 gesendet, was die Bestätigung an den Adapter zurückgibt.
5. **Abschluss**: Nach dem initialen Lesevorgang wird das INITO-Ereignis ausgegeben, zusammen mit den Statusinformationen QO und STATUS. Nach Schreibvorgängen über den Adapter erfolgt kein INITO, sondern nur eine Bestätigung über VAL.EI1.

## Technische Besonderheiten
- Der Baustein verwendet die Eclipse 4diac-Infrastruktur und importiert Typen aus `eclipse4diac::storage` und `adapter::types::bidirectional::AR2`.
- Der AR2-Adapter ermöglicht eine klare Trennung zwischen Lese- und Schreibzugriffen über einen einzigen Adapter-Socket.
- Standardmäßig wird die Datei `settings.ini` im Arbeitsverzeichnis der Applikation erwartet. Der genaue Pfad kann über die INI-Block-Konfiguration angepasst werden (nicht direkt im INI_AR2 sichtbar).
- Der Baustein ist für REAL-Daten ausgelegt; für andere Datentypen müssten entsprechende Varianten erstellt werden.
- Die Fehlerbehandlung erfolgt über den STATUS-Ausgang und QO.
- Das INITO-Ereignis wird nur nach dem initialen Lesevorgang ausgelöst, nicht nach Schreibvorgängen über den Adapter. Schreibvorgänge werden nur über den Adapter quittiert.

## Zustandsübersicht
Da es sich um einen Composite-FB handelt, gibt es keinen expliziten internen Zustandsautomaten. Der Ablauf ergibt sich aus dem Event-Netzwerk:
- INIT empfangen → INI.INIT ausführen.
- Nach INI.INITO: automatisch INI.GET ausführen.
- Nach INI.GETO: VAL.EI1 auslösen (Wertausgabe) und INITO senden.
- Bei Empfang von VAL.EO1 (neuer Wert von außen): INI.SET ausführen, danach INI.SETO → VAL.EI1 (Bestätigung an Adapter, kein INITO).

## Anwendungsszenarien
- **Parameterverwaltung**: Speichern und Laden von Einstellungen (z.B. PID-Reglerparameter, Sollwerte) aus einer Konfigurationsdatei.
- **Initiale Konfiguration**: Beim Start einer Anwendung werden vorgegebene Werte aus der settings.ini geladen.
- **Online-Parametrierung**: Über eine HMI oder ein Leitsystem können zur Laufzeit neue Werte über den AR2-Adapter geschrieben werden, die der Baustein sofort in die Datei speichert und bestätigt.
- **Redundanz**: Falls keine Datei vorhanden ist, wird der DEFAULT_VALUE verwendet, sodass die Anwendung auch ohne Konfiguration starten kann.

## Vergleich mit ähnlichen Bausteinen
- **INI (eclipse4diac::storage::INI)**: Der INI_AR2 erweitert den Basis-INI-Baustein um eine Adapter-Schnittstelle, sodass er leichter in eine übergeordnete Struktur eingebunden werden kann. Der INI-Baustein benötigt separate Event-Anbindung für Lesen und Schreiben; INI_AR2 vereinfacht dies durch den bidirektionalen Adapter.
- Andere Speicherbausteine (z.B. für Datenbanken oder OPC UA): INI_AR2 ist auf einfache INI-Dateien begrenzt, aber sehr leichtgewichtig und ohne zusätzliche Laufzeitabhängigkeiten.

## Fazit
Der INI_AR2-Funktionsblock bietet eine kompakte und einfach zu integrierende Lösung zum persistenten Speichern und Laden von REAL-Konfigurationswerten. Durch die Verwendung eines AR2-Adapters wird die Anbindung an andere Komponenten standardisiert. Der Baustein eignet sich besonders für Embedded-Steuerungen mit geringen Anforderungen an die Datenhaltung, bei denen eine INI-Datei ausreichend ist.