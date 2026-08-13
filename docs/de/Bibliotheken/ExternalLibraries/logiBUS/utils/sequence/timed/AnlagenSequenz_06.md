# AnlagenSequenz_06

![AnlagenSequenz_06_ecc](./AnlagenSequenz_06_ecc.svg)

![AnlagenSequenz_06](AnlagenSequenz_06.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AnlagenSequenz_06` ist ein zeitgesteuerter Ring-Sequenzer für die geordnete
Start- und Stopp-Reihenfolge von sechs Motoren (M1..M6), wie sie z. B. bei einer
Getreideannahme-Förderkette benötigt wird. Anders als die generischen Bausteine
[sequence_T_04](sequence_T_04.md)/[sequence_T_08](sequence_T_08.md) ist er kein
Allzweck-Sequenzer, sondern hart auf dieses eine Anwendungsmuster zugeschnitten: Vorlauf (Motoren
schalten von hinten nach vorne der Reihe nach ein) und Nachlauf (Motoren schalten von vorne nach
hinten der Reihe nach aus) sind zwei getrennte, rein lineare Ketten, die über die beiden
Ring-Pole `sAUS` (unten, alle Motoren aus) und `sLAEUFT` (oben, alle Motoren an) zu einem
geschlossenen Ring verbunden sind. Zusätzlich besitzt der Baustein eine vollständige
Störungs-Kaskade: Meldet einer der sechs Motoren während des Hoch- oder Herunterfahrens oder im
Dauerbetrieb eine Störung, springt der FB in einem einzigen Schritt (kein Nachfassen über mehrere
Zyklen) in den passenden Nachlauf-Zustand, der genau die zu diesem Zeitpunkt noch laufenden
vorgeordneten Motoren berücksichtigt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

*   **`EIN`**: Startet die Vorlauf-Kette (Übergang `sAUS` → `sVOR1`). Nur wirksam, wenn
    `EINSCHALTBEREIT = TRUE` (Bedingung `EIN[NOT (STOERUNG_M1 OR ... OR STOERUNG_M6)]`); quittiert
    dabei zugleich eine anstehende, verriegelte `STATUS_STOERUNG`-Anzeige.
*   **`AUS`**: Löst die Stopp-Sequenz aus jedem Schritt der Vorlauf-Kette (`sVOR1`..`sVOR5`) oder
    aus `sLAEUFT` aus. Springt auf den jeweiligen Spiegelpunkt der Nachlauf-Kette
    (`sVOR_k` → `sNACH_(6-k)`), da hier kein Motor-Fehler, sondern nur ein Bedienerwunsch vorliegt.
*   **`EI_M1`**: Störungsstatus Motor 1 hat sich geändert. Führt (`With STOERUNG_M1`) aus jedem
    Zustand vor `sNACH1` direkt dorthin.
*   **`EI_M2`**: Störungsstatus Motor 2 hat sich geändert. Führt (`With STOERUNG_M2`) direkt nach
    `sNACH2`.
*   **`EI_M3`**: Störungsstatus Motor 3 hat sich geändert. Führt (`With STOERUNG_M3`) direkt nach
    `sNACH3`.
*   **`EI_M4`**: Störungsstatus Motor 4 hat sich geändert. Führt (`With STOERUNG_M4`) direkt nach
    `sNACH4`.
*   **`EI_M5`**: Störungsstatus Motor 5 hat sich geändert. Führt (`With STOERUNG_M5`) direkt nach
    `sNACH5`.
*   **`EI_M6`**: Störungsstatus Motor 6 hat sich geändert. Führt (`With STOERUNG_M6`) direkt nach
    `sAUS` (M6 ist der letzte/äußerste Motor der Kette, es gibt keinen kürzeren Nachlauf-Schritt).

### **Ereignis-Ausgänge**

*   **`CNF`**: Ausführungsbestätigung, ausgelöst bei jedem Zustandswechsel; liefert
    `STATUS_BETRIEB`, `STATUS_STOERUNG`, `ZAEHLSTAND` und `EINSCHALTBEREIT`.
*   **`EO_M1`**: Laufbefehl Motor 1 aktualisiert; liefert `DO_M1` (analog `EO_Sx` in
    `sequence_T_04`/`_08`).
*   **`EO_M2`**: Laufbefehl Motor 2 aktualisiert; liefert `DO_M2`.
*   **`EO_M3`**: Laufbefehl Motor 3 aktualisiert; liefert `DO_M3`.
*   **`EO_M4`**: Laufbefehl Motor 4 aktualisiert; liefert `DO_M4`.
*   **`EO_M5`**: Laufbefehl Motor 5 aktualisiert; liefert `DO_M5`.
*   **`EO_M6`**: Laufbefehl Motor 6 aktualisiert; liefert `DO_M6`.

### **Daten-Eingänge**

*   **`ZE1_EIN` .. `ZE5_EIN`** (TIME): Verweildauer je Vorlauf-Schritt (`sVOR1`→`sVOR2` bis
    `sVOR5`→`sLAEUFT`), bevor automatisch der nächste Motor dazugeschaltet wird. Initialwert:
    `NO_TIME`.
*   **`ZE1_AUS` .. `ZE5_AUS`** (TIME): Verweildauer je Nachlauf-Schritt (`sNACH1`→`sNACH2` bis
    `sNACH5`→`sAUS`), bevor automatisch der nächste Motor abgeschaltet wird. Initialwert:
    `NO_TIME`.
*   **`STOERUNG_M1` .. `STOERUNG_M6`** (BOOL): Live-Störungssignal je Motor, dauerhaft (kein
    Puls). Initialwert: `FALSE`.

### **Daten-Ausgänge**

*   **`STATUS_BETRIEB`** (SINT): 0=Aus, 1=Hochfahren, 2=Läuft, 3=Herunterfahren.
*   **`STATUS_STOERUNG`** (SINT): 0=keine, 4=aktiv — bleibt bis zur nächsten erfolgreichen
    `EIN`-Quittierung verriegelt (siehe Technische Besonderheiten).
*   **`EINSCHALTBEREIT`** (BOOL): `TRUE` nur wenn `ZAEHLSTAND = 0` (alle Motoren stehen) UND alle
    sechs `STOERUNG_Mx` aktuell `FALSE` sind.
*   **`ZAEHLSTAND`** (SINT): 0..6, Anzahl der aktuell laufenden Motoren.
*   **`DO_M1` .. `DO_M6`** (BOOL): Laufbefehl je Motor.

### **Adapter**

*   **`timeOut`** (Plug, Typ: `iec61499::events::ATimeOut`): Standardisierter TimeOut-Adapter für
    die Zeitsteuerung der Vor- und Nachlauf-Schritte, analog zur Nutzung in `sequence_T_04`.

## Funktionsweise

Der FB ist ein Basic Function Block (BFB) mit 12 realen Zuständen plus Startzustand, angeordnet
als Ring aus zwei linearen Ketten:

1.  **Vorlauf-Kette** (`sVOR1` → `sVOR2` → `sVOR3` → `sVOR4` → `sVOR5` → `sLAEUFT`): Jeder Schritt
    schaltet genau einen weiteren Motor dazu, in der Reihenfolge M6, M5, M4, M3, M2, M1 (die
    Motoren mit der höchsten Nummer starten zuerst). Der Übergang zum jeweils nächsten Schritt
    erfolgt automatisch nach Ablauf der zugehörigen `ZEk_EIN`-Zeit (`timeOut.TimeOut`).
2.  **Nachlauf-Kette** (`sNACH1` → `sNACH2` → `sNACH3` → `sNACH4` → `sNACH5` → `sAUS`): Spiegelbild
    des Vorlaufs — jeder Schritt schaltet genau einen Motor ab, in der Reihenfolge M1, M2, M3, M4,
    M5, M6.
3.  **Start**: `EIN` (nur aus `sAUS`, nur wenn `EINSCHALTBEREIT`) quittiert eine anstehende
    `STATUS_STOERUNG`-Anzeige und aktiviert `sVOR1`.
4.  **Geplanter Stopp**: `AUS` aus jedem Vorlauf-Schritt oder aus `sLAEUFT` springt auf den
    Spiegelpunkt der Nachlauf-Kette (`sVOR_k` → `sNACH_(6-k)`, `sLAEUFT` → `sNACH1`) — es werden
    nur die zu diesem Zeitpunkt tatsächlich laufenden Motoren nachträglich der Reihe nach
    abgeschaltet, keine bereits stehenden erneut angefasst.
5.  **Störungs-Kaskade**: Jedes `EI_Mx`-Ereignis (`With STOERUNG_Mx`) hat aus jedem Zustand vor
    seinem Zielschritt eine direkte Ein-Schritt-Transition zum passenden `sNACH_x`
    (bzw. zu `sAUS` bei `x=6`). Dadurch reagiert der FB auf jede Störung sofort, unabhängig davon,
    ob sich der Ring gerade im Vor- oder Nachlauf oder im Dauerbetrieb (`sLAEUFT`) befindet — ohne
    Umweg über einen Spiegelpunkt und ohne mehrzyklisches Nachfassen.
6.  **Dauerbetrieb**: `sLAEUFT` ist der obere Ring-Pol — alle sechs Motoren laufen, keine
    Zeitsteuerung aktiv, der FB verbleibt hier bis `AUS` oder einer Störungsmeldung.
7.  **Zyklusende**: Nach `sNACH5` (oder direkt aus einer Störung) erreicht der Ring wieder `sAUS`
    — den Ruhezustand, aus dem heraus ein neuer `EIN`-Zyklus beginnen kann.

## Technische Besonderheiten

*   **`EINSCHALTBEREIT` ist bewusst NICHT an `STATUS_STOERUNG` gekoppelt.** `STATUS_STOERUNG`
    bleibt nach einer Störung bis zur nächsten erfolgreichen `EIN`-Quittierung verriegelt (dient
    der Anzeige in der Visu). Würde `EINSCHALTBEREIT` davon abhängen, könnte der `EIN`-Taster nach
    der allerersten jemals aufgetretenen Störung nie wieder freigegeben werden — echter Deadlock.
    `EINSCHALTBEREIT` prüft stattdessen die *live* `STOERUNG_Mx`-Signale direkt
    (`(ZAEHLSTAND = 0) AND NOT (STOERUNG_M1 OR ... OR STOERUNG_M6)`).
*   **Der `sAUS → sVOR1`-Übergang trägt zusätzlich die volle Interlock-Bedingung im
    Event-Bracket** (`EIN[NOT (STOERUNG_M1 OR ... OR STOERUNG_M6)]`), nicht nur eine Prüfung auf
    den berechneten Status. Ein reiner Statuswert wie `EINSCHALTBEREIT` erzwingt für sich genommen
    nichts — nur eine tatsächliche `ECTransition Condition` verhindert den Start bei anstehender
    Störung.
*   **Events sind polar und werden nicht mit `AND`/`OR` verknüpft.** Alle Bedingungen, die ein
    Ereignis mit einer Datenbedingung kombinieren, nutzen ausschließlich die Klammer-Syntax
    `EventName[boolean_ausdruck]` (z. B. `EI_M3[STOERUNG_M3]`) — die einzige gültige Form dafür in
    IEC 61499.
*   **Keine Selbstschleifen mehr im ECC.** Eine frühere Fassung nutzte ein zyklisches `EI_CYCLIC`
    -Ereignis zum Nachfassen über mehrere Zyklen; das ist entfernt. `EI_CYCLIC_Auswertung` läuft
    stattdessen als Entry-Algorithmus in jedem aktiven Zustand mit und wertet
    `STOERUNG_M1..M6` bei jedem Zustandswechsel neu aus.
*   **Direkte Ein-Schritt-Störungsdispatch statt Spiegelpunkt-Umweg.** Jeder Zustand vor einem
    `sNACH_x` hat eine eigene, direkte `EI_Mx`-Transition dorthin (51 Kanten insgesamt für die
    Störungs-Kaskade) — kein Zwischenschritt über einen Spiegelpunkt wie beim geplanten `AUS`.
*   **`MaxBetriebRest`/Nachlauf-Reste (Demo-Server-Schema) sind noch nicht abgebildet** — bewusste,
    dokumentierte Vereinfachung der aktuellen Fassung (s. Kommentar im FB-Header).

## Zustandsübersicht

| Zustandsname | Beschreibung | Aktive Motoren | Übergangsbedingung zum nächsten Zustand |
| :--- | :--- | :--- | :--- |
| **xSTART** | Initialer Idle-Zustand. | — | `1` (sofort nach `sAUS`) |
| **sAUS** | Ring-Grundzustand, unten. | keine | `EIN[NOT (STOERUNG_M1..M6)]` → `sVOR1` |
| **sVOR1** | Vorlauf-Schritt 1. | M6 | `timeOut.TimeOut` → `sVOR2`; `AUS` → `sNACH5`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sVOR2** | Vorlauf-Schritt 2. | M5, M6 | `timeOut.TimeOut` → `sVOR3`; `AUS` → `sNACH4`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sVOR3** | Vorlauf-Schritt 3. | M4, M5, M6 | `timeOut.TimeOut` → `sVOR4`; `AUS` → `sNACH3`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sVOR4** | Vorlauf-Schritt 4. | M3, M4, M5, M6 | `timeOut.TimeOut` → `sVOR5`; `AUS` → `sNACH2`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sVOR5** | Vorlauf-Schritt 5. | M2, M3, M4, M5, M6 | `timeOut.TimeOut` → `sLAEUFT`; `AUS` → `sNACH1`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sLAEUFT** | Ring-Pol, oben — Dauerbetrieb. | M1..M6 (alle) | `AUS` → `sNACH1`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sNACH1** | Nachlauf-Schritt 1 (M1 gestoppt). | M2..M6 | `timeOut.TimeOut` → `sNACH2`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sNACH2** | Nachlauf-Schritt 2 (M1, M2 gestoppt). | M3..M6 | `timeOut.TimeOut` → `sNACH3`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sNACH3** | Nachlauf-Schritt 3 (M1..M3 gestoppt). | M4, M5, M6 | `timeOut.TimeOut` → `sNACH4`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sNACH4** | Nachlauf-Schritt 4 (M1..M4 gestoppt). | M5, M6 | `timeOut.TimeOut` → `sNACH5`; `EI_Mx` → passendes `sNACHx`/`sAUS` |
| **sNACH5** | Nachlauf-Schritt 5 (M1..M5 gestoppt). | M6 | `timeOut.TimeOut` → `sAUS`; `EI_M6` → `sAUS` |

**Globale Störungs-Kaskade**: Aus jedem Zustand vor einem `sNACH_x` führt `EI_Mx[STOERUNG_Mx]`
direkt und ohne Umweg in genau diesen Zustand (bzw. nach `sAUS` bei `x=6`) — insgesamt 51 solcher
Direkt-Kanten, siehe Netzwerkdiagramm.

## Anwendungsszenarien

*   **Getreideannahme-Förderkette**: Sechs in Reihe geschaltete Förderelemente (z. B. Elevator,
    Querförderer, Trog- und Schneckenförderer), die nur in einer festen Reihenfolge sicher an- und
    abgeschaltet werden dürfen, damit kein Element gegen einen stehenden Nachfolger fördert.
*   **Mehrstufige Förderanlagen allgemein**: Jede Anlage mit einer festen Kaskade aus Motoren, bei
    der eine Störung an einer Stelle einen kontrollierten, aber sofortigen Rückzug der
    vorgeordneten Stufen erfordert.
*   **Sicherheitskritische Ablaufketten**: Prozesse, bei denen ein einfacher zeitgesteuerter
    Sequenzer nicht ausreicht, weil zusätzlich eine verriegelte Störungsanzeige und ein
    Wiederanlauf-Interlock (`EINSCHALTBEREIT`) benötigt werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

*   **[sequence_T_04](sequence_T_04.md) / [sequence_T_08](sequence_T_08.md)**: Generische,
    lineare Zeitsequenzer mit 4 bzw. 8 Schritten und einem einzigen Reset-Pfad. `AnlagenSequenz_06`
    verwendet denselben `ATimeOut`-Adapter-Mechanismus, ist aber kein generischer Baustein — die
    Ring-Topologie (zwei gekoppelte lineare Ketten), das feste 6-Motoren-Muster je Schritt und die
    direkte Ein-Schritt-Störungs-Kaskade sind fest einprogrammiert, nicht konfigurierbar.
*   **Einfache Timer-Ketten (TON-Verkettung)**: Müssten Zustandslogik, Motor-Muster je Schritt und
    Störungsbehandlung von Hand nachbilden. `AnlagenSequenz_06` kapselt das vollständig inklusive
    Interlock-Logik.
*   **Zähler-/ereignisbasierte Sequenzer**: Schalten auf externe Trigger statt auf Zeit weiter.
    `AnlagenSequenz_06` ist speziell für den Fall gedacht, dass die Verweildauer je Schritt fest
    vorgegeben ist (Anlaufzeit der Motoren), mit Störungen als einzigem asynchronen
    Unterbrechungspfad.

## Fazit

`AnlagenSequenz_06` bündelt eine komplette, sicherheitsrelevante Start-/Stopp-Logik für sechs in
Reihe arbeitende Motoren in einem einzigen Baustein: geordneter Vor- und Nachlauf über zwei
gekoppelte lineare Ketten, ein verriegelter Störungsstatus mit explizitem Wiederanlauf-Interlock,
und eine direkte, verzögerungsfreie Störungs-Kaskade aus jedem Betriebszustand heraus. Durch die
klare Trennung von Ring-Topologie (ECC), Motor-Schaltlogik (Algorithmen) und Zeitsteuerung
(`timeOut`-Adapter) bleibt der Baustein trotz seiner Komplexität wartungsfreundlich und reduziert
den Programmieraufwand im übergeordneten Application-Netzwerk erheblich.
