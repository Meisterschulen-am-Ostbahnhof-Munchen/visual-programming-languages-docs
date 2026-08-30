# INI_AB

![INI_AB](INI_AB.svg)

* * * * * * * * * *

## Einleitung

`INI_AB` lädt und speichert einen `BYTE`-Wert in der `settings.ini`-Datei, adressiert über Abschnitt (`SECTION`) und Schlüssel (`KEY`). Er ist das `settings.ini`-Gegenstück zu [NVS_AB](../esp32_nvs/NVS_AB.md) und verwendet dieselbe Zwei-Adapter-Architektur mit unidirektionalen `AB`-Adaptern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisiert den Baustein und liest den unter `SECTION`/`KEY` hinterlegten Wert (bzw. `DEFAULT_VALUE`, falls noch keiner existiert). Liefert `QI`, `SETM`, `SECTION`, `KEY`, `DEFAULT_VALUE`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt Initialisierung und den ersten Lesezugriff, liefert `QO` und `STATUS`.

### **Daten-Eingänge**

- **QI** (BOOL): Qualifizierer des `INIT`-Ereignisses.
- **SETM** (BOOL): Gibt das Spiegeln (Rückmeldung) beim Schreiben (`SET`) frei.
- **SECTION** (STRING): Name des Abschnitts in der `settings.ini`.
- **KEY** (STRING): Name des Schlüssels innerhalb des Abschnitts.
- **DEFAULT_VALUE** (BYTE): Wert, der geliefert wird, wenn unter `SECTION`/`KEY` noch nichts in der `settings.ini` gespeichert ist.

### **Daten-Ausgänge**

- **QO** (BOOL): Erfolgsqualifizierer, mit `INITO` sowie den internen Adapterbestätigungen mitgeliefert.
- **STATUS** (STRING): Statusmeldung des Dateizugriffs.

### **Adapter**

- **AB_IN** (Socket, Typ `AB`): Neuer zu speichernder Wert -- ein Adapterereignis auf `AB_IN.E1` löst einen `SET` im internen INI-Baustein aus, `AB_IN.D1` liefert den zu schreibenden Wert.
- **AB_OUT** (Plug, Typ `AB`): Gibt den zuletzt gelesenen Wert aus -- sowohl nach dem automatischen Erstlesen bei `INIT` als auch nach jedem bestätigten Schreibvorgang (`AB_OUT.D1`/`AB_OUT.E1`).

## Funktionsweise

`INI_AB` kapselt intern eine Instanz von `eclipse4diac::storage::INI` sowie ein `E_PERMIT`-Gatter (`SET_PERMIT`). Bei `INIT` wird die interne INI-Instanz initialisiert (`INI.INIT`) und anschließend automatisch ein `GET` ausgelöst, das den unter `SECTION`/`KEY` gespeicherten Wert (oder `DEFAULT_VALUE`) liefert; das Ergebnis wird über `AB_OUT` ausgegeben, `INITO` bestätigt den Abschluss.

Zum Schreiben liefert der an `AB_IN` angeschlossene Baustein ein Adapterereignis (`AB_IN.E1`) mit dem neuen Wert (`AB_IN.D1`); dies löst `INI.SET` aus. Ob die erfolgreiche Speicherung zusätzlich über `AB_OUT` zurückgemeldet wird, steuert `SETM`: Ist `SETM` gesetzt, gibt `SET_PERMIT` das `AB_OUT.E1`-Ereignis nach erfolgreichem `SET` frei ("Mirroring").

## Technische Besonderheiten

- Reines Composite-FB ohne eigene ECC -- die eigentliche Dateizugriffslogik steckt in der internen `INI`-Instanz, `INI_AB` verdrahtet nur Ereignisse und Daten zwischen ihr und den beiden `AB`-Adaptern.
- Zwei getrennte, unidirektionale Adapter (`AB_IN`/`AB_OUT`) statt eines einzigen bidirektionalen -- dadurch lassen sich Lese- und Schreibpfad an unterschiedliche Gegenstellen anschließen, was mit [INI_AB2](INI_AB2.md) (ein gemeinsamer `AB2`-Socket) nicht möglich ist.
- Adressierung über `SECTION` **und** `KEY` (statt nur `KEY` bei den `NVS_*`-Bausteinen) entspricht dem klassischen INI-Dateiformat.

## Zustandsübersicht

Der Baustein ist zustandslos im Sinne einer eigenen ECC: Er durchläuft bei `INIT` einmalig Initialisierung + Erstlesen, danach reagiert er auf jedes `AB_IN`-Adapterereignis mit einem INI-Schreibzugriff und optional einer Bestätigung über `AB_OUT`.

## Anwendungsszenarien

- Persistieren einzelner `BYTE`-Konfigurationswerte (z. B. Betriebsmodus, Kanalauswahl) in einer menschenlesbaren `settings.ini`
- Aufbau eines Lese-/Schreibpaars, bei dem Lese- und Schreibseite an unterschiedliche Bausteine angeschlossen werden sollen
- Konfigurationsdateien, die auch außerhalb der Steuerung (z. B. per Texteditor) einsehbar/änderbar sein sollen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [INI_AB2](INI_AB2.md), das denselben Zweck über einen einzigen bidirektionalen `AB2`-Adapter statt zweier unidirektionaler `AB`-Adapter erfüllt, sowie mit [NVS_AB](../esp32_nvs/NVS_AB.md), das dieselbe Schnittstelle für den ESP32-NVS-Flash-Speicher statt für die `settings.ini` bereitstellt.

## Fazit

`INI_AB` bietet einen einfachen, unidirektional verdrahteten Zugriff auf einen persistenten `BYTE`-Wert in der `settings.ini` und eignet sich überall dort, wo Lese- und Schreibpfad getrennt geführt werden sollen.
