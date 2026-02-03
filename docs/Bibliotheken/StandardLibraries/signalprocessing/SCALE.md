# SCALE

```{index} single: SCALE
```

<img width="668" height="239" alt="SCALE" src="https://github.com/user-attachments/assets/b3a2d282-98ec-47f2-a311-70f4d8aa9d90" />

* * * * * * * * * *
## Einleitung
Der SCALE-Funktionsblock dient zur Skalierung eines Eingangswertes von einem Eingangsbereich auf einen Ausgangsbereich. Dies ist besonders nützlich in der Signalverarbeitung, wenn Werte aus einem Messbereich in einen anderen Bereich transformiert werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Skalierungsoperation. Wird mit den Daten-Eingängen IN, MAX_IN, MIN_IN, MAX_OUT und MIN_OUT verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die Beendigung der Skalierungsoperation.

### **Daten-Eingänge**
- **IN**: Der Eingangswert, der skaliert werden soll (REAL).
- **MAX_IN**: Der maximale Wert des Eingangsbereichs (REAL).
- **MIN_IN**: Der minimale Wert des Eingangsbereichs (REAL).
- **MAX_OUT**: Der maximale Wert des Ausgangsbereichs (REAL).
- **MIN_OUT**: Der minimale Wert des Ausgangsbereichs (REAL).

### **Daten-Ausgänge**
- **(unnamed)**: Der skalierte Ausgangswert (REAL).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der SCALE-Funktionsblock berechnet den skalierten Wert nach folgender Formel:
```
SCALE := (IN - MIN_IN) * (MAX_OUT - MIN_OUT) / (MAX_IN - MIN_IN) + MIN_OUT;
```
Diese Formel transformiert den Eingangswert linear vom Eingangsbereich [MIN_IN, MAX_IN] auf den Ausgangsbereich [MIN_OUT, MAX_OUT].

## Technische Besonderheiten
- Der Funktionsblock ist in ST (Structured Text) implementiert.
- Die Berechnung erfolgt in einem einzigen Schritt, was eine hohe Effizienz gewährleistet.
- Keine Zustandsverwaltung erforderlich, da es sich um eine statische Transformation handelt.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Operation wird bei jedem REQ-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Skalierung von Sensorwerten (z.B. von 4-20 mA auf 0-100 %).
- Transformation von Messwerten für die Anzeige oder Weiterverarbeitung.
- Allgemeine Signalverarbeitung in industriellen Steuerungssystemen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Skalierungsbausteinen ist SCALE besonders einfach und direkt in der Anwendung.
- Keine zusätzlichen Parameter oder komplexen Einstellungen erforderlich.
- Ideal für einfache lineare Skalierungen ohne zusätzliche Logik.




## 🛠️ Zugehörige Übungen

* [Uebung_042](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_042.md)

## Fazit
Der SCALE-Funktionsblock bietet eine effiziente und einfache Lösung für lineare Skalierungsaufgaben. Seine klare Schnittstelle und direkte Implementierung machen ihn zu einem wertvollen Baustein in der Signalverarbeitung.