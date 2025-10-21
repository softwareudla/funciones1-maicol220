import javax.swing.*;

public class Ventana {
    private JPanel Ventana;
    private JTabbedPane tabbedPane1;

    // REGISTRO
    private JTextField txtId;
    private JTextField txtNombre;
    private JComboBox<String> cboUniverso;
    private JTextField txtNivel;
    private JComboBox<String> cboHabilidad;
    private JButton btnAgregar;
    private JButton btnLimpiar;

    // MOSTRAR
    private JButton btnMostrar;
    private JTextArea textAreaLista;

    // SUMAR
    private JComboBox<String> cboHabilidadSum;
    private JButton btnSumar;
    private JLabel lblSuma;

    private final ColaSuperHeroe cola = new ColaSuperHeroe();

    public Ventana() {
        if (cboUniverso.getItemCount() == 0) {
            cboUniverso.addItem("Marvel");
            cboUniverso.addItem("DC");
        }
        if (cboHabilidad.getItemCount() == 0) {
            cboHabilidad.addItem("Fuerza");
            cboHabilidad.addItem("Vuelo");
            cboHabilidad.addItem("Velocidad");
            cboHabilidad.addItem("Telepatía");
        }
        if (cboHabilidadSum.getItemCount() == 0) {
            cboHabilidadSum.addItem("Fuerza");
            cboHabilidadSum.addItem("Vuelo");
            cboHabilidadSum.addItem("Velocidad");
            cboHabilidadSum.addItem("Telepatía");
        }

        textAreaLista.setEditable(false);
        textAreaLista.setLineWrap(true);
        textAreaLista.setWrapStyleWord(true);
        lblSuma.setText(" ");

        txtId.addActionListener(e -> btnAgregar.doClick());
        txtNombre.addActionListener(e -> btnAgregar.doClick());
        txtNivel.addActionListener(e -> btnAgregar.doClick());

        btnAgregar.addActionListener(e -> onAgregar());
        btnLimpiar.addActionListener(e -> limpiarCampos());
        btnMostrar.addActionListener(e -> textAreaLista.setText(cola.listar()));
        btnSumar.addActionListener(e -> onSumar());
    }

    private void onAgregar() {
        String idTxt = txtId.getText().trim();
        String nombre = txtNombre.getText().trim();
        String universo = String.valueOf(cboUniverso.getSelectedItem());
        String nivelTxt = txtNivel.getText().trim();
        String habilidad = String.valueOf(cboHabilidad.getSelectedItem());

        if (idTxt.isEmpty() || nombre.isEmpty() || nivelTxt.isEmpty()) {
            JOptionPane.showMessageDialog(null, "Complete todos los campos.");
            return;
        }
        int id, nivel;
        try {
            id = Integer.parseInt(idTxt);
            nivel = Integer.parseInt(nivelTxt);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "ID y Nivel deben ser numéricos.");
            return;
        }

        cola.encolar(new SuperHeroe(id, nombre, universo, nivel, habilidad));
        JOptionPane.showMessageDialog(null, "Superhéroe agregado.");
        limpiarCampos();
    }

    private void onSumar() {
        String habilidad = String.valueOf(cboHabilidadSum.getSelectedItem());
        double total = cola.sumarPorHabilidad(habilidad);
        lblSuma.setText("Suma total de poder (" + habilidad + "): " + total);
    }

    private void limpiarCampos() {
        txtId.setText("");
        txtNombre.setText("");
        txtNivel.setText("");
        cboUniverso.setSelectedIndex(0);
        cboHabilidad.setSelectedIndex(0);
        txtId.requestFocus();
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("SuperHéroes");
        frame.setContentPane(new Ventana().Ventana);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(860, 540); // o frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
