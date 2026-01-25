# F_MUX_3

```{index} single: F_MUX_3
```

<img width="1366" height="254" alt="F_MUX_3" src="https://github.com/user-attachments/assets/2dbe8298-6066-469e-96d6-1a6850de8bd8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_MUX_3` ist ein Multiplexer, der drei Eingangssignale basierend auf einem Steuersignal auswählt und an den Ausgang weiterleitet. Er ist Teil der IEC 61131-3 Standardbibliothek und dient zur Signalauswahl in Automatisierungsanwendungen.

![F_MUX_3](F_MUX_3.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Service Request – löst die Auswahl und Weiterleitung des entsprechenden Eingangssignals aus. Verknüpft mit den Daten-Eingängen `IN1`, `IN2`, `IN3` und `K`.

### **Ereignis-Ausgänge**
- **CNF**: Confirmation of Requested Service – bestätigt die erfolgreiche Auswahl und Weiterleitung des Signals. Verknüpft mit dem Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **K** (ANY_INT): Steuersignal, das angibt, welcher Eingang ausgewählt wird (0 für `IN1`, 1 für `IN2`, 2 für `IN3`).
- **IN1** (ANY): Eingangswert 1.
- **IN2** (ANY): Eingangswert 2.
- **IN3** (ANY): Eingangswert 3.

### **Daten-Ausgänge**
- **OUT** (ANY): Ausgangswert, der dem ausgewählten Eingang entspricht (`IN1` für `K = 0`, `IN2` für `K = 1`, `IN3` für `K = 2`).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei einem `REQ`-Ereignis wertet der Funktionsblock den Wert von `K` aus und leitet den entsprechenden Eingang (`IN1`, `IN2` oder `IN3`) an den Ausgang `OUT` weiter. Anschließend wird das `CNF`-Ereignis ausgelöst, um die erfolgreiche Operation zu bestätigen.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen (`ANY`) für die Eingänge und den Ausgang.
- Der Steuereingang `K` muss ein ganzzahliger Typ (`ANY_INT`) sein.
- Initialwerte für die Eingänge sind nicht vordefiniert.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Auswahl und Weiterleitung erfolgt unmittelbar bei einem `REQ`-Ereignis.

## Anwendungsszenarien
- Signalweiterleitung in Steuerungsanwendungen.
- Auswahl zwischen verschiedenen Sensordaten.
- Dynamische Konfiguration von Signalpfaden.

## Vergleich mit ähnlichen Bausteinen
- `F_MUX_2`: Ein einfacherer Multiplexer mit nur zwei Eingängen.
- `F_SEL`: Ein allgemeinerer Selektor, der möglicherweise komplexere Auswahlkriterien unterstützt.

## Fazit
Der `F_MUX_3` ist ein einfacher und effizienter Multiplexer für Anwendungen, bei denen zwischen drei Signalen ausgewählt werden muss. Seine Flexibilität in Bezug auf Datentypen macht ihn vielseitig einsetzbar.