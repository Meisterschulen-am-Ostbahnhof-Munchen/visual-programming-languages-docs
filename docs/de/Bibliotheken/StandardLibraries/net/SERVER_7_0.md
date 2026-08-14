# SERVER_7_0

![SERVER_7_0](SERVER_7_0.svg)

* * * * * * * * * *
## Einleitung

Der `SERVER_7_0`-Funktionsblock ist die generische Server-Variante mit 7 Sende- und 0 Empfangsdatenfeldern für die Kommunikation mit einem passenden [CLIENT_0_7](CLIENT_0_7.md)-Block. Er überträgt 7 Datenwerte (`SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7`) an den Client, ohne Rückgabedaten zu empfangen. Wie alle `SERVER_*`-Bausteine basiert er auf der generischen `GEN_SERVER`-Implementierung — dieselbe C++-Basis wie [CLIENT_1](CLIENT_1.md)/[SERVER_1](SERVER_1.md), lediglich die Anzahl der Sende-/Empfangsfelder unterscheidet sich pro Instanziierung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Aktiviert den Server für eine Client-Verbindung (QI = TRUE) bzw. schließt ihn (QI = FALSE), trägt `QI` und `ID`.
- **RSP**: Sendet Daten an den Client, trägt `QI` sowie `SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt Verbindungsauf-/-abbau, trägt `QO` und `STATUS`.
- **IND**: Signalisiert, dass neue Daten vom Client verfügbar sind, trägt `QO`, `STATUS`.

### **Daten-Eingänge**

- **QI** (BOOL): Steuert den Verbindungsstatus (`TRUE` = Verbindung öffnen, `FALSE` = Verbindung schließen).
- **ID** (WSTRING): Identifikator der Verbindung (z. B. Zieladresse/Port).
- **SD_1** (ANY): Sendedatum 1, wird mit `RSP` an den Client übertragen.
- **SD_2** (ANY): Sendedatum 2, wird mit `RSP` an den Client übertragen.
- **SD_3** (ANY): Sendedatum 3, wird mit `RSP` an den Client übertragen.
- **SD_4** (ANY): Sendedatum 4, wird mit `RSP` an den Client übertragen.
- **SD_5** (ANY): Sendedatum 5, wird mit `RSP` an den Client übertragen.
- **SD_6** (ANY): Sendedatum 6, wird mit `RSP` an den Client übertragen.
- **SD_7** (ANY): Sendedatum 7, wird mit `RSP` an den Client übertragen.

### **Daten-Ausgänge**

- **QO** (BOOL): Aktueller Verbindungsstatus.
- **STATUS** (WSTRING): Statusinformationen zur Verbindung.
- Keine Empfangsdaten (`SERVER_7_0` erhält keine Nutzdaten über `IND`, nur Verbindungs-/Statusinformationen).

## Funktionsweise

`SERVER_7_0` initialisiert über `INIT` eine Verbindung zum passenden `CLIENT_0_7`-Block (bei `QI = TRUE`) bzw. schließt sie (bei `QI = FALSE`); der Abschluss wird über `INITO` bestätigt. Über `RSP` werden `SD_1` `SD_2` `SD_3` `SD_4` `SD_5` `SD_6` `SD_7` an den Client übertragen. Sobald eine Antwort vorliegen, löst der Baustein `IND` aus.

## Technische Besonderheiten

- **Generische Implementierung**: `eclipse4diac::core::GenericClassName = 'GEN_SERVER'`, dieselbe C++-Basis wie alle anderen `SERVER_*`-Varianten; Anzahl und Typ (`ANY`) der Sende-/Empfangsfelder werden pro Instanziierung über die Typdefinition festgelegt.
- **`ANY`-Datenfelder**: Alle `SD_i`/`RD_i` sind generisch (`ANY`) typisiert und passen sich beim Verdrahten an den jeweils angeschlossenen Datentyp an.
- **Gegenstück `CLIENT_0_7`**: `SERVER_7_0` ist funktional nur mit einem `CLIENT_0_7`-Block auf der Client-Seite kompatibel — die Anzahl der Sendefelder der einen Seite muss der Anzahl der Empfangsfelder der Gegenseite entsprechen.

## Zustandsübersicht

1. **Nicht verbunden**: Initialzustand, `QO = FALSE`.
2. **Verbindungsaufbau**: `INIT` mit `QI = TRUE` wird verarbeitet.
3. **Verbunden**: `INITO` mit `QO = TRUE` bestätigt die Verbindung.
4. **Datenaustausch**: `RSP`/`IND`-Zyklus für Sende-/Empfangsdaten.
5. **Verbindungstrennung**: `INIT` mit `QI = FALSE` wird verarbeitet.

## Anwendungsszenarien

- **Kommunikation zwischen verteilten Steuerungssystemen**, bei denen genau 7 Werte gesendet und 0 Werte empfangen werden sollen, ohne überzählige, ungenutzte Datenfelder in Kauf zu nehmen.
- **Server-seitige Anbindung** eines Kommunikationspartners, der bereits als `CLIENT_0_7` mit passender Feldanzahl ausgelegt ist.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[CLIENT_0_7](CLIENT_0_7.md)**: das direkte Gegenstück auf der Client-Seite, mit vertauschter Sende-/Empfangsfeldanzahl.
- **[CLIENT_1](CLIENT_1.md) / [SERVER_1](SERVER_1.md)**: dieselbe generische Implementierung mit je einem Sende- und Empfangsfeld.

## Fazit

`SERVER_7_0` liefert die generische, auf 7 Sende- und 0 Empfangsfelder zugeschnittene Server-Variante der `GEN_SERVER`-Familie und eignet sich für Netzwerkverbindungen, deren Nutzdatenanzahl von der Standardvariante mit einem Feld abweicht.
