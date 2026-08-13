# NVS_AB

![NVS_AB](NVS_AB.svg)

* * * * * * * * * *
## Einleitung

`NVS_AB` lädt und speichert einen `BYTE`-Wert unter einem Schlüssel (`KEY`) im nichtflüchtigen Speicher (Non-Volatile Storage, NVS) des ESP32. Im Unterschied zum bidirektionalen [NVS_AB2](NVS_AB2.md) verwendet er zwei getrennte unidirektionale `AB`-Adapter: einen Socket zum Schreiben (`AB_IN`) und einen Plug zum Lesen/Bestätigen (`AB_OUT`).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisiert den Baustein und liest den unter `KEY` hinterlegten Wert (bzw. `DEFAULT_VALUE`, falls noch keiner existiert). Liefert `QI`, `SETM`, `KEY`, `DEFAULT_VALUE`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt Initialisierung und den ersten Lesezugriff, liefert `QO` und `STATUS`.

### **Daten-Eingänge**

- **QI** (BOOL): Qualifizierer des `INIT`-Ereignisses.
- **SETM** (BOOL): Gibt das Spiegeln (Rückmeldung) beim Schreiben (`SET`) frei.
- **KEY** (STRING): Name des Schlüssels im NVS.
- **DEFAULT_VALUE** (BYTE): Wert, der geliefert wird, wenn unter `KEY` noch nichts im NVS gespeichert ist.

### **Daten-Ausgänge**

- **QO** (BOOL): Erfolgsqualifizierer, mit `INITO` sowie den internen Adapterbestätigungen mitgeliefert.
- **STATUS** (STRING): Statusmeldung des NVS-Zugriffs.

### **Adapter**

- **AB_IN** (Socket, Typ `AB`): Neuer zu speichernder Wert -- ein Adapterereignis auf `AB_IN.E1` löst einen `SET` im internen NVS-Baustein aus, `AB_IN.D1` liefert den zu schreibenden Wert.
- **AB_OUT** (Plug, Typ `AB`): Gibt den zuletzt gelesenen Wert aus -- sowohl nach dem automatischen Erstlesen bei `INIT` als auch nach jedem bestätigten Schreibvorgang (`AB_OUT.D1`/`AB_OUT.E1`).

## Funktionsweise

`NVS_AB` kapselt intern eine Instanz von `logiBUS::storage::esp32_nvs::NVS` sowie ein `E_PERMIT`-Gatter (`SET_PERMIT`). Bei `INIT` wird die interne NVS-Instanz initialisiert (`NVS.INIT`) und anschließend automatisch ein `GET` ausgelöst, das den unter `KEY` gespeicherten Wert (oder `DEFAULT_VALUE`) liefert; das Ergebnis wird über `AB_OUT` ausgegeben, `INITO` bestätigt den Abschluss.

Zum Schreiben liefert der an `AB_IN` angeschlossene Baustein ein Adapterereignis (`AB_IN.E1`) mit dem neuen Wert (`AB_IN.D1`); dies löst `NVS.SET` aus. Ob die erfolgreiche Speicherung zusätzlich über `AB_OUT` zurückgemeldet wird, steuert `SETM`: Ist `SETM` gesetzt, gibt `SET_PERMIT` das `AB_OUT.E1`-Ereignis nach erfolgreichem `SET` frei ("Mirroring").

## Technische Besonderheiten

- Reines Composite-FB ohne eigene ECC -- die eigentliche Flash-Logik steckt in der internen `NVS`-Instanz, `NVS_AB` verdrahtet nur Ereignisse und Daten zwischen ihr und den beiden `AB`-Adaptern.
- Zwei getrennte, unidirektionale Adapter (`AB_IN`/`AB_OUT`) statt eines einzigen bidirektionalen -- dadurch lassen sich Lese- und Schreibpfad an unterschiedliche Gegenstellen anschließen, was mit [NVS_AB2](NVS_AB2.md) (ein gemeinsamer `AB2`-Socket) nicht möglich ist.
- `SETM` steuert nur, ob ein Schreibvorgang zusätzlich per Adapterereignis über `AB_OUT` gespiegelt wird -- gespeichert wird in jedem Fall.

## Zustandsübersicht

Der Baustein ist zustandslos im Sinne einer eigenen ECC: Er durchläuft bei `INIT` einmalig Initialisierung + Erstlesen, danach reagiert er auf jedes `AB_IN`-Adapterereignis mit einem NVS-Schreibzugriff und optional einer Bestätigung über `AB_OUT`.

## Anwendungsszenarien

- Persistieren einzelner `BYTE`-Konfigurationswerte (z. B. Betriebsmodus, Kanalauswahl) auf dem ESP32
- Aufbau eines Lese-/Schreibpaars, bei dem Lese- und Schreibseite an unterschiedliche Bausteine angeschlossen werden sollen
- Wiederherstellen eines zuletzt gespeicherten `BYTE`-Werts nach einem Neustart über `AB_OUT`

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [NVS_AB2](NVS_AB2.md), das denselben Zweck über einen einzigen bidirektionalen `AB2`-Adapter statt zweier unidirektionaler `AB`-Adapter erfüllt, sowie mit [INI_AB](../ini/INI_AB.md), das dieselbe Schnittstelle für die textbasierte `settings.ini` statt für den NVS-Flash-Speicher bereitstellt.

## Fazit

`NVS_AB` bietet einen einfachen, unidirektional verdrahteten Zugriff auf einen persistenten `BYTE`-Wert im ESP32-NVS und eignet sich überall dort, wo Lese- und Schreibpfad getrennt geführt werden sollen.
